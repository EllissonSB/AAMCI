#include "stm32f4xx_hal.h"
#include "dht22.h"

DHT22_HandleTypeDef hdht22;
  
int main(void) {
  // Inicialize o hardware STM32
  
  // Inicialize o sensor DHT22
  
  DHT22_Init(&hdht22, GPIOA, 0);
  
  // Leitura dos dados do sensor
  float temperature, humidity;
  if (DHT22_ReadData(&hdht22, &temperature, &humidity) == DHT22_OK)
  {
    // Dados lidos com sucesso
    // Faça algo com a temperatura e umidade
    printf("Temperatura: %.2f °C\n", temperature);
    printf("Umidade: %.2f %%\n", humidity);
  } 
  else 
  {
    // Erro ao ler os dados do sensor
    printf("Falha ao ler os dados do sensor DHT22\n");
  }
  
  while (1) {
      // Loop principal do seu programa
  }
}
