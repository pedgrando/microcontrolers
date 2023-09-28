# Atividade 1
## Alunos
Erik Melges 			NUSP: 12547399
Gabriel Sotto Rodrigues		NUSP: 11800952
Pedro A. B. Grando		NUSP: 12541766

# CODIGO 1

```
org 0000h

main:
	MOV ACC, #35h ; move imediatamente 35h para o reg ACC - 2µs
	MOV ACC, #00h ; move imediatamente zero para o reg ACC - 2µs
	
	; garante a selecao do banco 0 de reg
	CLR RS0 ;1µs
	CLR RS1 ;1µs
	
	MOV R0, #10h 	; move imediatamente 10h para R0 - 1µs
	MOV B, #01h 		; move imediatamente 01h para B - 2µs
 	
	MOV 00h, P1 		; move a porta P1 para o endereço 00h - 2µs
	
	SETB RS0 			; seleciona o banco de reg 1 - 1µs
	
	MOV R0, 00h 		; move o conteudo do endereco 00h para R0 - 2µs
	MOV 10h, R0 		; move o conteudo de R0 para o endereco 10h - 2µs
	MOV R1, #10h		; move o valor 10h para R1 - 1µs
	MOV A, @R1   	; move o valor que esta no endereco guardado por R1 para ACC - 1µs
	MOV DPTR, #9A5Bh	; move o valor 9A5Bh para DPTR - 2µs
	
	NOP; -1µs
  	JMP $ 				; trava o programa nessa linha - 2µs

END
```
Resposta da questão (a):
	o tempo de cada instrução está comentada no final de cada linha do código. Sendo o tempo total de 23µs.

Resposta da questão (b):
	23 ciclos de máquina

Resposta da questão (c): 
	O que acontece é que você está lendo o valor dos 8 bits da porta P1 e carregando esse valor no registrador A. Esse valor é setado em FF porque a porta está em nível lógico alto.

Resposta da questão (d):
	Todos os bits do acumulador são mudados para 1, ficando o valor 1111 1111.

Resposta da questão (e):
	Visualiza-se mudanças nos registrados especiais DPH e DPL, logo, por se tratar de dois registradores, podemos mover valores de 4 digitos(16 bits) para o DPTR, sendo seu valor máximo FFFF.

# CODIGO 2

```
org 0000h

main:
	MOV ACC, #2 ; move imediatamente 2 para o reg ACC
	MOV B, #3 ; move imediatamente 3 para o reg B
	MOV 00h, #7 ; move imediatamente 7 para o endereco 00h
	ADD A, 00h ; adiciona ao ACC o valor no endereco 00h
	SUBB A, #3 ; subtrai 3 do ACC
	INC B  ; incrementa B
	SUBB A, B ; subtrai B de A
	MUL AB ; multiplica A e B, e zera B
	INC B ; incrementa B
	INC B ; incrementa B
	DIV AB ; divide A por B, e zera B
	MOV 01h, A ; move imediatamente o valor de A para o endereco 01h
	MOV 02h, B ; move imediatamente o valor de B para o endereco 02h

	JMP main ; salta para o inicio do codigo

END
```
São feitas diversas operações aritiméticas com ACC e B: inicialmente, ACC = 2 e B = 3; soma-se #7, que está no endereço 00h, a ACC que agora vale 9; subtrai-se #3 de ACC, resultando em 6; incrementa-se B, até 4; subtrai-se B (4) de ACC (6), que agora vale 2; multiplica-se ACC (2) e B (4) e o resultado vai para ACC (8), e zera-se B; incrementa-se B duas vezes, resultando em 2; divide-se ACC (8) por B (2) e o resultado vai para ACC (4), zera-se B; os valores são salvos ena memória e reinica-se o programa.

O bit menos significativo do PSW é o bit de paridade do acumulador: ele é 1 se o valor é par e 0 se é ímpar.

# CODIGO 3

```
org 0000

inicio:
	MOV ACC, #00000001b; move de forma indireta para o valor para ACC
	MOV B,	#00000011b; move de forma indireta para o valor para B

	ANL A, B; ADN logico entre A e B
	RR A; rotaciona A a direita
	RR A; rotaciona A a direita

	CPL A; complemento de A
	ORL A, B; OR logico entre A e B
	XRL A, B; XOR logico entre A e B

	SWAP A; realiza o swap de A
	jmp inicio ; salta para a label inicio
end; encerra o programa
```
A medida que as operações lógicas são realizadas, observa-se as alterações em binário no ACC.


# CODIGO 4

```
org 0000h

ajmp main ; salta para o bloco principal do codigo

org 0033h

;bloco principal do codigo
main:
	CLR A 				;limpa o acumulador
	MOV R0, #10		;move imediatamente 10 para R0
	
bloco1:
	JZ bloco2			; se ACC == 0 salta para bloco2
	JNZ bloco3		; se ACC != 0 salta para bloco3
	NOP					; no operation

bloco2:
	MOV A, R0 		; move o valor de R0 para ACC
	AJMP bloco1 	; salta para o bloco 1

bloco3:
	DEC R0                  ; decrementa R0
	CJNE R0, #0, bloco3     ; enquanto R0 != 0 salta para bloco3
	AJMP main               ; salta para a main 
	 

end
```
O código basicamente funciona como um loop eterno. Inicialmente, na seção principal do código, faz-se o reset do acumulador, para o caso de essa não ser a primeira execução do loop, e na sequência, atribui-se 10 ao registrador R0. Na sequência, o código é fracionado em três blocos: o primeiro, que é executado logo na sequência, verifica se o acumulador está zerado ou não, saltando para o bloco 2 em caso afirmativo, e para o bloco 3 em caso negativo; o segundo bloco apenas atribui a A o valor de R0 e volta para o bloco 1; por fim, o terceiro bloco é outro loop, em que se decrementa R0 até que ele seja 0. Basciamente, o fluxo de código será atribuir 10 a R0 e zerar A, saltar para o bloco 2, atribuir um valor não nulo a A, voltar para o bloco 1, saltar para o bloco3, zerar R0 em um loop e reiniciar esse processo.
