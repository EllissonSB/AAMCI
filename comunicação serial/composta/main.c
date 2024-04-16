/* Descrição:
 Implementação de uma comunicação serial composta controlada por software:
 - O pino PA0 opera em dreno aberto como pino de comunicação entre duas placas
 - Os pinos PA0 de duas placas devem ser interligados juntamente com o GND
 - Os botões K0 e K1 acionam, respectivamente, os LEDs D2 e D3 da outra placa (operação remota)
 - Há um buzzer no pino PA1 para sinalizar o envio de um dado]
 - O botão K0 da PLACA0 comanda o LED D2 da PLACA1; 
 - O botão K1 da PLACA0 comanda o LED D2 da PLACA2;
 - O botão K0 da PLACA1 comanda o LED D2 da PLACA0;
 - O botão K1 da PLACA1 comanda o LED D3 da PLACA2;
 - O botão K0 da PLACA2 comando o LED D3 da PLACA0;
 - O botão K1 da PLACA2 comando o LED D3 da PLACA1;

 - Identificação da placa:
 * 0x00 -> PLACA 0
 * 0x01 -> PLACA 1
 * 0x02 -> PLACA 2
 - Identificação do LEDs:
 * 0xAA -> LED 0
 * 0xBB -> LED 1
 - Identificação da chave:
 *GPIOE->IDR & (1 << 4) K0
 *GPIOE->IDR & (1 << 3) K1
*/

#include "stm32f4xx.h"		//inclusão das definições do microcontrolador
#include "Utility.h"		//biblioteca de funções úteis de temporização

#define	TEMPO_BIT	10		//duração de umbit (em us)
#define	NUM_BITS	8		//quantidade de bits de dados no frame
#define Num_Placa   0x00	// Identificação da placa, essa placa é a 0 Alterar conforme gravação na placa
//Protótipos de funções
void GPIO_Config(void);		//configura os pinos utilizados
void envia_cmd(uint8_t uint8_t);	//função para enviar um comando no barramento
uint8_t recebe_cmd(void);	//função para receber um comando
void buzzer(void);			//função de ativação do buzzer

int main(void)
{
	Utility_Init();		//inicializa o sistema de clock e funções de temporização
	GPIO_Config();		//configura os pinos utilizados
	Delay_ms(100);		//aguarda sinais estabilizarem

	while(1)
	{
		if(!(GPIOE->IDR & (1 << 4)))			//verifica se PE4 foi pressionado
		{
			envia_cmd(0xAA,0x01);				// Alterar conforme gravação na placa
			buzzer();							//sinaliza o fim do envio 100ms
			Delay_ms(75);						//filtro de bouncing
			while(!(GPIOE->IDR & (1 << 4)));	//aguarda o botão ser solto
		}

		if(!(GPIOE->IDR & (1 << 3)))			//verifica se PE3 foi pressionado
		{
			envia_cmd(0xAA,0x02);				// Alterar conforme gravação na placa
			buzzer();							//sinaliza o fim do envio
			Delay_ms(75);						//filtro de bouncing
			while(!(GPIOE->IDR & (1 << 3)));	//aguarda o botão ser solto
		}

		if(!(GPIOA->IDR & 1))	//verifica se há start bit
		{
			uint8_t recebido = recebe_cmd();	//recebe o comando
			if(recebido == 0xAA)
			{
				GPIOA->ODR ^= 1 << 6;			//alterna o estado do LED em PA6
			}
			if(recebido == 0xBB)
			{
				GPIOA->ODR ^= 1 << 7;			//alterna o estado do LED em PA7
			}
		}
	}
}


//Função de configuração dos pinos
void GPIO_Config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN;	//habilita o clock do GPIOA e GPIOE
	GPIOA->ODR |= (1<<7) | (1<<6) | 1;		//inicia com leds e buzzer desligados e linha COM em idle
	GPIOA->OTYPER |= 1;						//saída open-drain em PA0
	GPIOA->PUPDR |= 0b01;					//habilita pull-up em PA0
	GPIOA->MODER |= (0b01 << 14) | (0b01 << 12) | (0b01 << 2) | (0b01) ; 	//pinos PA0, PA1, PA6 e PA7 no modo saída
	GPIOE->PUPDR |= (0b01 << 8) | (0b01 << 6);		//habilita pull-up em PE4 e PE3
}

//Função para envio de um comando
void envia_cmd(uint8_t dado, uint8_t num_placa)
{
  uint8_t aux=dado;
	GPIOA->ODR &= ~1;		//start bit (nível baixo)
	Delay_us(TEMPO_BIT);	//aguarda tempo do start bit
	for(uint8_t counter=NUM_BITS; counter; --counter) //envia os bits do comando
	{
		if(dado & 1)			//testa se o LSB é 1
			GPIOA->ODR |= 1;	//linha de dados em nível alto
		else
			GPIOA->ODR &= ~1;	//linha de dados em nível baixo
		Delay_us(TEMPO_BIT);	//aguarda o tempo do bit
		dado >>= 1;				//desloca os bits para envio posterior
	}
	GPIOA->ODR |= 1;		//stop bit (nível alto)
	Delay_us(TEMPO_BIT);	//tempo do stop bit
	for(uint8_t counter=NUM_BITS; counter; --counter) //envia os bits do comando
	{
		if(num_placa & 1)			//testa se o LSB é 1
			GPIOA->ODR |= 1;	//linha de dados em nível alto
		else
			GPIOA->ODR &= ~1;	//linha de dados em nível baixo
		Delay_us(TEMPO_BIT);	//aguarda o tempo do bit
		num_placa >>= 1;				//desloca os bits para envio posterior
	}
	GPIOA->ODR |= 1;		//stop bit (nível alto)
	Delay_us(TEMPO_BIT);	//tempo do stop bit
	Delay_us(TEMPO_BIT/2);	//tempo para verificar se houve a comunicação
	if((GPIOA->IDR & 1)){ //se não houve a comunicação ligar o led da placa na qual foi apertado o botão.
		if(aux == 0xAA)
		{
			GPIOA->ODR ^= 1 << 6;			//alterna o estado do LED em PA6
		}
		if(aux == 0xBB)
		{
			GPIOA->ODR ^= 1 << 7;			//alterna o estado do LED em PA7
		}
	}
	
}

//Função para recebimento de um comando
uint8_t recebe_cmd(void)
{
	uint8_t dado_recebido = 0;
	uint8_t placa_recebido = 0;
	Delay_us(TEMPO_BIT/2);	//aguarda metade do start bit
	if(!(GPIOA->IDR & 1))	//confirma que houve um start bit
	{
		for(uint8_t counter=NUM_BITS; counter; --counter)	//leitura dos bits
		{
			Delay_us(TEMPO_BIT);	//aguarda o tempo do bit
			dado_recebido >>= 1;	//desloca para receber o próximo bit

			if(GPIOA->IDR & 1)
				dado_recebido |= (1 << (NUM_BITS-1));
			else
				dado_recebido &= ~(1 << (NUM_BITS-1));
		}

		Delay_us(TEMPO_BIT);		//aguarda para fazer leitura do stop bit
		for(uint8_t counter=NUM_BITS; counter; --counter)	//leitura dos bits
		{
			Delay_us(TEMPO_BIT);	//aguarda o tempo do bit
			placa_recebido >>= 1;	//desloca para receber o próximo bit

			if(GPIOA->IDR & 1)
				placa_recebido |= (1 << (NUM_BITS-1));
			else
				placa_recebido &= ~(1 << (NUM_BITS-1));
		}

		Delay_us(TEMPO_BIT);
		if((GPIOA->IDR & 1) && placa_recebido==Num_Placa)		//confirma que houve um stop bit e se o dado é para placa respectiva.
		{
			Delay_us(TEMPO_BIT/2);	//aguarda o fim do tempo do stop bit
			GPIOA->ODR &= ~1;	//linha de dados em nível baixo
			Delay_us(TEMPO_BIT);	//aguarda o tempo do bit
			GPIOA->ODR |= 1;	//linha de dados em nível alto
			return dado_recebido; 	//retorna o dado recebido
		}
		else
			return 0;	//não houve recepção do stop bit, aborta recepção
	}
	else
		return 0;		//não houve recepção do start bit, aborta recepção
}

//Função de sinalização de fim de envio de dado
void buzzer(void)
{
	GPIOA->ODR |= 1 << 1;			//liga o buzzer
	Delay_ms(10);					//aguarda
	GPIOA->ODR &= ~(1 << 1);		//desliga o buzzer
	Delay_ms(80);					//aguarda
	GPIOA->ODR |= 1 << 1;			//liga o buzzer
	Delay_ms(10);					//aguarda
	GPIOA->ODR &= ~(1 << 1);		//desliga o buzzer
}
