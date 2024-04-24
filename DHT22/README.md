# Biblioteca para DHT22
![image](https://github.com/EllissonSB/AAMCI/assets/57837838/b0b9df77-36cb-4275-97bb-f0028adac35e)

Esta é uma biblioteca em linguagem C para o sensor de temperatura e umidade DHT22, projetada para ser utilizada em plataformas STM32. Ela oferece uma interface simples para ler os dados de temperatura e umidade do sensor, facilitando a integração em projetos STM32.

## Pré-requisitos

Certifique-se de que o ambiente de desenvolvimento para STM32 esteja configurado corretamente e que você tenha acesso às bibliotecas de periféricos necessárias.

## Instalação

1. Clone este repositório em sua máquina local:

```bash
$ git clone https://github.com/seu_usuario/biblioteca-dht22.git
```
2. Copie os arquivos da biblioteca (`dht22.c` e `dht22.h`) para o diretório do seu projeto STM32.

3. Inclua os arquivos da biblioteca em seu projeto:

```c
#include "dht22.h"
```

## Uso
Aqui está um exemplo de como utilizar esta biblioteca em seu código STM32:
```c
#include "stm32f4xx_hal.h"
#include "dht22.h"

DHT22_HandleTypeDef hdht22;

int main(void) {
    // Inicialize o hardware STM32
    
    // Inicialize o sensor DHT22
    DHT22_Init(&hdht22, GPIO_PORT, GPIO_PIN);
    
    // Leitura dos dados do sensor
    float temperature, humidity;
    if (DHT22_ReadData(&hdht22, &temperature, &humidity) == DHT22_OK) {
        // Dados lidos com sucesso
        // Faça algo com a temperatura e umidade
    } else {
        // Erro ao ler os dados do sensor
    }
    
    while (1) {
        // Loop principal do seu programa
    }
}

```
Substitua GPIO_PORT e GPIO_PIN pelos pinos aos quais o seu sensor DHT22 está conectado.

# Contribuindo
Contribuições são bem-vindas! Para sugestões, correções ou novos recursos, sinta-se à vontade para abrir uma issue ou enviar um pull request.

# Créditos
Esta biblioteca foi desenvolvida por Ellisson Barbosa. Qualquer feedback ou contribuição é apreciada.
