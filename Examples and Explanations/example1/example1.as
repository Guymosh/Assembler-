.entry LIST
.entry MAIN
.extern W
;asd rf sdfgfdg 




MAIN: 	add 	r3,	LIST
LOOP:	prn #48
	lea W,r6
	inc r6



	mov r3,K
	sub r1,r4
	bne END
	cmp K, #-6
	bne &END 
	dec W
STR:	.string "abcd"

	jmp &LOOP
LIST: 	.data 6,-9
	add L3 ,L3
END: 	stop



	.data -100
K: 	.data 31
.extern L3
