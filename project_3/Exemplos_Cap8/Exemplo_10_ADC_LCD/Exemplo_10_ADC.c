   // SEL0433/SEL0614/SEL0336 - Aplic. de Microprocessadores
    // Conceitos sobre conversor AD - config. manual dos registradores
    
 // Uso do conversor ADC para realizar uma leitura anal�gica (sinal de tens�o)
  // usando o TRIMPOT "ADC Input" do kit EasyPIC v7

  // ser� o usado o canal anal�gico AN4/RA5 - para ler o sinal de tens�o anal�gico
  //o qual ir� varir conforme o ajuste do TRIMPOT (simulando uma varia��o anal�gica
  // um sensor, por exemplo)

  // Device:  PIC18F4550 - Clock  = 8 MHz
  // Tens�o de ref. interna do ADC 0 - 5V
  // Necess�rio add bibliotecas LCD e convers�o de dados em "Libray Manager"

  // Configura��es necess�rias: Jumper no "trimpot ADC input" AN4 (PORTA5) - 1� trimpot
  // habilitar o display LCD em SW4 - se necess�rio ajsutar o contraste no trimpot
  // correspondente


// Config. de pinos do LCD  (PORTB) conforme exemplo da biblioteca do compilador

// pinos utilizados para comunica��o com o display LCD
sbit LCD_RS at LATB4_bit; // pino 4 do PORTB interligado ao RS do display
sbit LCD_EN at LATB5_bit; // pino 5 do PORTB " " ao EN do display
sbit LCD_D4 at LATB0_bit; // pino 0 do PORTB ao D4
sbit LCD_D5 at LATB1_bit;  // " "
sbit LCD_D6 at LATB2_bit;  // " "
sbit LCD_D7 at LATB3_bit;  // " "
// dire��o do fluxo de dados nos pinos selecionados
sbit LCD_RS_Direction at TRISB4_bit;  // dire��o do fluxo de dados do pino RB4
sbit LCD_EN_Direction at TRISB5_bit;  // " "
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;


 // inicio do programa
void main() {
  unsigned int Leitura_ADC;   // variav. de leitura ADC
  unsigned char Texto[10];//Display LCD - tipo char - int 8 bits (lembrando: Arranjo= tipo nome [n� de elementos])


TRISA.RA0 = 1;  // pino AN0 como entrada (canal anal�gico escolhido neste ex.)
//PORTA.RA0 = 1;  // opcional   (pull-up)

// 3 reg. respons�veis pela config. do m�dulo ADC: ADCON0, ADCON1 e ADCON2
// ver config. dos bits no datasheet  https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/39632e.pdf

ADCON0 = 0B00001101;  // AN0 -> AD ligado, leitura deslig., canal AN0
ADCON1 = 0B00000000; // tens�es de ref. internas = VDD e Vss

ADCON2 = 0B10101010; // Justificativa para direita, FOSC/32 (tempo entre 2 e 25 us)
//... e 12 TAD (tempo de convers�o de cada bit + 2 TAD)

// Config. do m�dulo LCD
  Lcd_Init();                        //Inicializa display no modo 4 bits
  Lcd_Cmd(_LCD_CLEAR);               //Apaga display
  Lcd_Cmd(_LCD_CURSOR_OFF);          //Desliga cursor
  Lcd_Out(1,1,"ADC: ");              // escrita: Linha x Coluna

 while(1)
 {
   ADCON0.GO_DONE = 1;           //liga a leitura e inicia a convers�o do ADC
     while(ADCON0.GO_DONE == 1);   //Aguardar o t�rmino da convers�o - ap�s a
     //convers�o terminar esse bit ser�  = 0 e essa condi��o n�o � mais
     // verdadeira. Sendo assim, o programa vai para a pr�xima linha


     //Leitura_ADC = ADRESH + ADRESL;//0 a 1023; em que: '|' = OR bit a bit
    Leitura_ADC = ((ADRESH << 8)| ADRESL);
    /*
     ex.: se ADRESH = 0B00000011;
     ( ADRESH << 8) =>  00000011 00000000   // rota��o de 8 bits a esquerda para
     que o valor de ADRESH fique na parte alta
     Lembrando que Leitura ADC � uma vari�vel de 16 bits que receber� a combina��o
     de ADRESH (8bits) com ADRESL(8bits) por meio do OR bitwise "|"   entre eles
     
     Lembrando tamb�m que somente 10 bits ser�o usados para leitura do ADC, j� que
     sua resolu��o � 10 bits. A opera��o acima, portanto, usar� 2 bits do ADRESH
     e 8 bits do ADRESL (justificando o valor da covers�o a direita)
     
     Portanto, supondo ADRESH = 0B00000011; e ADRESL =  0B10011101 ; � necess�rio
     a opera��o acima para formar a palavra de 10 bits "11 + 10011101" = 1110011101

    Dessa forma, o OR bitwise de ADRESH e ADRESL sera:

                      00000011 00000000
                    | 00000000 10011101
    leitura_ADC =  <- 00000011 10011101 (resultado da Op. OR) - 10 bits justificado a direita

    */

      
    // mostrar os valores no display LCD = necessaio habilitar bibliotecas de
    //LCD (as linhas de c�digo foram apresentadas anteriomente)
    // e de convers�o dos dados (Leitura_ADC) para texto, apresentadas abaixo
    WordToStr(Leitura_ADC, Texto);  // convers�o
    LCD_Out(1,5, Texto); // coloca o texto em determinada linha e posi��o 1, 5
    Delay_ms(20);       // delay para dar tempo para o LCD atualizar

   }

}