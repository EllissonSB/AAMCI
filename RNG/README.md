## **Jogo de Melhor de 3 com RNG STM32**

---

## Visão Geral

Bem-vindo ao Jogo de Melhor de 3 com RNG (Random Number Generator) STM32! Este projeto simula um jogo simples no qual o usuário compete contra o computador em uma série de três rodadas. Cada rodada gera um número aleatório tanto para o usuário quanto para o computador, e o vencedor é determinado com base no valor gerado. O objetivo é ser o primeiro a alcançar dois pontos.

---

## Instruções de Uso

1. **Configuração do Hardware:**
   - Certifique-se de ter um microcontrolador STM32 compatível com o gerador de números aleatórios (RNG).

2. **Configuração do Software:**
   - Baixe o código-fonte deste projeto e abra-o em seu ambiente de desenvolvimento para STM32.

3. **Compilação e Carregamento:**
   - Compile o código e carregue-o no microcontrolador STM32.

4. **Execução do Jogo:**
   - Ao iniciar o jogo, você será confrontado com uma série de três rodadas.
   - Em cada rodada, o programa gerará automaticamente um valor aleatório para você e para o computador.
   - O usuário pode pressionar a tecla "K" para iniciar cada rodada.
   - O vencedor de cada rodada é determinado comparando os valores gerados pelo usuário e pelo computador.
   - O jogador que obtiver o maior valor ganha um ponto naquela rodada.
   - O primeiro jogador a atingir dois pontos vence o jogo.

5. **Reiniciar o Jogo:**
   - Após o término do jogo, você pode reiniciar o jogo pressionando novamente a tecla "K".

---

## Exemplo de Funcionamento
```bash
Rodada 1:
  Valor do Usuário: 6
  Valor do Computador: 5
  O Usuário ganha esta rodada!

Rodada 2:
  Valor do Usuário: 2
  Valor do Computador: 6
  O Computador ganha esta rodada!

Rodada 3:
  Valor do Usuário: 4
  Valor do Computador: 1
  O Usuário ganha esta rodada!

O Usuário vence o jogo com 2 pontos!
```


---

## Considerações Finais

Este projeto demonstra uma implementação simples de um jogo de melhor de 3 utilizando o gerador de números aleatórios do microcontrolador STM32. Sinta-se à vontade para explorar, modificar e expandir este projeto de acordo com suas necessidades e interesses!

---
