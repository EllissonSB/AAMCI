#include "dht22.h"

void configure_timer_2(void){ //função para o timer ter incrementos a cada 1uS
    //O modo padrão do contador é com contagem crescente
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	//liga o clock do Timer2
	TIM2->PSC = 83;						//prescaler para incrementos a cada 1uS
	TIM2->EGR = TIM_EGR_UG;				//update event para escrever o valor do prescaler
	TIM2->CR1 |= TIM_CR1_CEN;	
}

void DHT22_Init(DHT22_HandleTypeDef* hdht22, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin){
    hdht22->GPIO_Port=GPIO_Port;
    hdht22->GPIO_Pin=GPIO_Pin;
    configure_timer_2();
    RCC->AHB1ENR |= (1 << ((uint32_t)GPIO_Port - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE)));// Habilita o clock do GPIO 
    GPIO_Port->OTYPER |= GPIO_Pin;  //pino como dreno aberto.
    GPIO_Port->PUPDR &= ~(0b11 << 2*GPIO_Pin);	//desabilita qualquer resistor
    GPIO_Port->PUPDR |= (0b01 << 2*GPIO_Pin);	//configura o resistor de pull-up
    GPIO_Port->MODER &= ~(0b11 << 2*GPIO_Pin);	//reseta os 2 bits do modo de operação
	GPIO_Port->MODER |= (0b01 << 2*GPIO_Pin);	//configura o modo de saída

   }
//Criação de atraso em us
void Delay_us(uint32_t delay)
{
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < delay);	//aguarda o tempo passar
}
//Criação de atraso em ms
void Delay_ms(uint32_t delay)
{
	uint32_t max = 1000*delay;
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < max);		//aguarda o tempo passar
}