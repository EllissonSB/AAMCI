/*
 * dht22.c
 *
 *      Author: ellisson
 */

#include "dht22.h"

void configure_timer_2(void){ //função para o timer ter incrementos a cada 1uS
    //O modo padrão do contador é com contagem crescente
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	//liga o clock do Timer2
	TIM2->PSC = 83;						//prescaler para incrementos a cada 1uS
	TIM2->EGR = TIM_EGR_UG;				//update event para escrever o valor do prescaler
	TIM2->CR1 |= TIM_CR1_CEN;
}
void enable_gpio_clock(GPIO_TypeDef *GPIOx){
    if (GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (GPIOx == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } 
	 else if (GPIOx == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
	 else if (GPIOx == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    }
}
void gpio_init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	enable_gpio_clock(GPIOx);
	GPIO_InitTypeDef GPIO_InitStruct;
	// Configuração dos pinos GPIO como saída com resistor de pull-up ativado
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Modo de saída push-pull
	GPIO_InitStruct.Pull = GPIO_PULLUP; // Resistor de pull-up ativado
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Alta Velocidade velocidade (opcional)
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void DHT22_Init(DHT22_HandleTypeDef* hdht22, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin){

	hdht22->GPIO_Port=GPIO_Port;
	hdht22->GPIO_Pin=GPIO_Pin;
	gpio_init(GPIO_Port,GPIO_Pin);
	configure_timer_2();
}
//Criação de atraso em us
void Delay_us(uint32_t delay){
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < delay);	//aguarda o tempo passar
}
//Criação de atraso em ms
void Delay_ms(uint32_t delay){
	uint32_t max = 1000*delay;
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < max);		//aguarda o tempo passar
}
int DHT22_ReadData(DHT22_HandleTypeDef* hdht22, float* temperature, float* humidity){
    hdht22->GPIO_Port->ODR &=~(1 << hdht22->GPIO_Pin);	//linha de dados em nível alto
    Delay_ms(1);
    hdht22->GPIO_Port->ODR |=(1 << hdht22->GPIO_Pin);
    Delay_us(40);
    if (!(hdht22->GPIO_Port->IDR & hdht22->GPIO_Pin)) //O pino está em nível logico down.
	{
        Delay_us (80);
        if(!(hdht22->GPIO_Port->IDR & hdht22->GPIO_Pin)) return 0;  // Não ocorreu comunicação retorna 0
    }
    while (hdht22->GPIO_Port->IDR & hdht22->GPIO_Pin);   // wait for the pin to go low
    uint16_t dados[2],data;
    uint8_t for_iterator_temp, for_iterator_bits;
    for (for_iterator_temp=0;for_iterator_temp++;for_iterator_temp<2){
        data=0;
        for (for_iterator_bits=0;for_iterator_bits++;for_iterator_bits<16){
            while(!(hdht22->GPIO_Port->IDR & hdht22->GPIO_Pin));
			Delay_us(40);
			if(!(hdht22->GPIO_Port->IDR & hdht22->GPIO_Pin))
			{
				data <<= 1;
			}
			else
			{
				data |= 1;
			}
        }
        dados[for_iterator_temp]=data;
    }
    temperature=(dados[0]/10)+1;
    humidity=(dados[1]/10)+1;
    return 1;
}
