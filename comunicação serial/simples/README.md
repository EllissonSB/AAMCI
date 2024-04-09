## Este é um exemplo de comunicação serial de 1 Byte, ou seja, 8 bits.
*Exemplo fazendo uso de um microcontrolador da família STM, com nomenclatura STM32F407VET6. Neste exemplo, foi feito o uso de dois microcontroladores mencionados anteriormente, de forma que ao apertar o push button de um microcontrolador, deveria acender um LED presente no outro. Caso a comunicação não seja concluída com sucesso, deve-se acender o LED da própria placa onde o push button foi pressionado.
* Neste exemplo, fez-se uso de um pacote de dados nesta configuração:
  * 1 bit de início (start bit).
  * 8 bits de informações.
  * 1 bit de fim (stop bit).
  * 1 bit de confirmação de transmissão.
* Utilizando o pino PA0 para comunicação, nas seguintes configurações:
  * Pino em dreno aberto.
  * Resistor de Pull-UP habilitado.
  * Pino em mode de saída.
*Utilizando os pinos PE3 e PE4 para os push buttons, nas seguintes configurações:
  *   Pino em modo de entrada.
  *   Resistor de Pull-UP habilitado.
* O código é composto por duas funções principais, que são: envia_cmd e recebe_cmd:
  * A função envia_cmd:
    * É a função responsável por enviar o dado referente ao push button e confirmar se realmente a comunicação ocorreu. Caso a comunicação não tenha ocorrido com sucesso, a função acende o LED referente.
  * A função recebe_cmd:
    * É a função responsável por receber os dados, confirmar a transmissão e acender o respectivo LED referente ao dado recebido.
