###CODIGO 1

```
org 0000h

main:
	MOV ACC, #35h ; move imediatamente 35h para o reg ACC
	MOV ACC, #00h ; move imediatamente zero para o reg ACC
	
	; garante a selecao do banco 0 de reg
	CLR RS0 
	CLR RS1
	
	MOV R0, #10h 	; move imediatamente 10h para R0
	MOV B, #01h 		; move imediatamente 01h para B
 	
	MOV 00h, P1 		; move a porta P1 para o endereço 00h
	
	SETB RS0 			; seleciona o banco de reg 1
	
	MOV R0, 00h 		; move o conteudo do endereco 00h para R0
	MOV 10h, R0 		; move o conteudo de R0 para o endereco 10h
	MOV R1, #10h		; move o valor 10h para R1
	MOV A, @R1   	; move o valor que esta no endereco guardado por R1 para ACC
	MOV DPTR, #9A5Bh	; move o valor 9A5Bh para DPTR
	
	NOP
  	JMP $ 				; trava o programa nessa linha

END
```



###CODIGO 2

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

###CODIGO 3

```
org 0000; coloca a origem em 00h

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



###CODIGO 4

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
