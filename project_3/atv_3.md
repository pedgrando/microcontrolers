# Prática 3

Nessa última prática, objetivou-se utilizar o microcontrolador PIC18F4550 para ler sinais analógicos controlados por um potenciometro, simulando um sensor de temperatura, discretizá-los com o uso de um ADC e expor os valores em um display LCD. Os códigos reunidos nesta pasta, de autoria do docente, aglutinam dois exemplos práticos nesse sentido.

### Membros:
- Erik Melges NUSP: 12547399
- Gabriel Sotto Rodrigues NUSP: 11800952
- Pedro Antonio Bruno Grando NUSP: 12547166

---
## Sobre os periféricos

Antes de comentar o código e a simulação, é interessante apontar conceitos interessantes e cruciais em relação ao uso dos periféricos citados acima. Primeiramente, o conversor analógico-digital é uma ferramente que, pela própria teoria de sinais, possue uma resolução intrínseca, relacionada ao número de bits para conversão, no nosso caso 10 bits. Isso limita os valores representáveis, bem como a sensibilidade à mudanças, uma vez que dado uma faixa de tensões de entrada analógica, só haverão 1024 (de 0 a 1023) correspondências discretas; i.e., dada uma alimentação de 0-5V, os valores representáveis estarão atrelados à sensibilidade de 10mV. Em segundo lugar, é preciso se atentar ao tempo de amostragem e à frequência do clock de conversão, o primeiro que é de 12 TADs e o segundo que deve se adequar a esse tempo. Por fim, é preciso lembrar que o display LCD utilizado nesse código está na configuração de 4 bits, o que significa que o envio de um caractér no padrão ANSII, com 8 bits, deve ser feito em duas partes.

---
## Código

Partindo agora para os códigos, é interessante comentar as configurações feitas para o uso dos periféricos nos exemplos, principalmente no que diz respeito ao ADC e ao LCD. No primeiro caso, configurou-se, nos registradores ADCON0, ADCON1 e ADCON2, um pino de entrada analógico A5, definiu-se a utilização de tensões Vcc e Vss internas (5 e 0 V, em ordem), justificou-se a saída, que é dividida em dois registradores (ADRESH e ADRESL) à direita, de forma que os bits sigam a ordem natural de distribuição, armazendo os bits menos significativos em ADRESL e os mais em ADRESH, adotou-se um frequência de oscilação de 1/32 do clock (corresponde a um período entre 2 e 25 micro segundos) e um período de conversão de 12 TADs, conforme o que foi calculado na disciplina. 

```
ADCON0 = 0B00001101;  // AN0 -> AD ligado, leitura deslig., canal AN0
ADCON1 = 0B00000000; // tensões de ref. internas = VDD e Vss
ADCON2 = 0B10101010; // Justificativa para direita, FOSC/32 (tempo entre 2 e 25 us) e 12 TAD (tempo de conversão de cada bit + 2 TAD)
```

No exemplo 11, foi configurado manualmente o registrador ADCON1, setando o pino A0 como entrada, mas o resto foi configurado através da função ADC_init(). Também foram utilizadas, em ambos os casos, bibliotecas padrões para o kit EasyPIC v7 que configuram o display LCD e fazem o envio de dados, de forma otimizada.

---
## Simulação

Foi também elaborada uma simulação mostrada abaixo no software SimulIDE, na qual foi carregado o código do exemplo 11 e se fez algumas execuções de teste. Note que no exemplo 11, os valores expostos no display ficam limitados entre 12.34 e 0. A pinagem do LCD foi conectada segundo as expecificações do fabricante da placa, que disponibilizou as bibliotecas.


![alt text](https://github.com/pedgrando/microcontrolers/blob/main/project_3/img/circuito.png?raw=true)

---
## Resultados e diposições finais

Tanto na execução do exemplo 10 em sala de aula quanto na simulação com o exemplo 11, foi possível observar o funcionamento do ADC através das variações de tensão geradas pelo potenciometro. Também foi possível entender o comportamento do display de LCD e todo o pré-processamento envolvido n

