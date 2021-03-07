





MAIN: 	add 	r3,	LIST
LOOP:	prn #48
	lea K,r6
	inc r6


;asd rf sdfgfdg 
	mov r3,K
	sub r1,r4
	bne END
	cmp K, #-6
	bne &END 
	dec K
STR:	.string "abcd"

	jmp &LOOP
LIST: 	.data 6,-9

END: 	stop



	.data -100
K: 	.data 31
