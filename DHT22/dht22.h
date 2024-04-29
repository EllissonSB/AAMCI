/*
 * dht22.h
 *
 *      Author: ellisson
 */


#ifndef DHT22_H
#define DHT22_H

#include "stm32f4xx.h"

typedef struct {
    GPIO_TypeDef* GPIO_Port;
    uint16_t GPIO_Pin;
} DHT22_HandleTypeDef;

void DHT22_Init(DHT22_HandleTypeDef* hdht22, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin);
int DHT22_ReadData(DHT22_HandleTypeDef* hdht22, float* temperature, float* humidity);
void enable_gpio_clock(GPIO_TypeDef* GPIOx);
void configure_timer_2(void);
void Delay_us(uint32_t delay);
void Delay_ms(uint32_t delay);
void gpoio_init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif /* DHT22_H */
