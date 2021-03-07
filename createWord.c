#include"header.h"
/*This file contain functions used for create words according to the action and prints errors if the operands in the source code are incorrect*/
extern int error;
/*This function creates word for mov action*/
void mov (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000000");
	strcpy(words.funct,"00000");
	mov_add_sub (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for cmp action*/
void cmp (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000001");
	strcpy(words.funct,"00000");
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
	/*checks the meun for first operand*/
	if(is_meun_0(firstOpr)==FALSE &&is_meun_1(firstOpr)==FALSE &&is_meun_3(firstOpr)==FALSE )
	{
		printf("Error! the source operand is invalid: %s line:%d\n",firstOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the first operand*/
	two_operands_first(firstOpr,srcCodeLine);
	/*checks the meun for second operand*/	
	if(is_meun_0(secondOpr)==FALSE &&is_meun_1(secondOpr)==FALSE &&is_meun_3(secondOpr)==FALSE)
	{
		printf("Error! the dest operand is invalid: %s line:%d\n",secondOpr,srcCodeLine);
		error=TRUE ;
	}	
	/*continue create the word according to the meun of the second operand*/
	two_operands_second(secondOpr,srcCodeLine);
}
/*This function creates word for add action*/
void add (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000010");
	strcpy(words.funct,"00001");
	mov_add_sub (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for sub action*/
void sub (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000010");
	strcpy(words.funct,"00010");
	mov_add_sub (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for lea action*/
void lea (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000100");
	strcpy(words.funct,"00000");
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
	/*checks the meun for first operand*/
	if(is_meun_1(firstOpr)==FALSE )
	{
		printf("Error! the source operand is invalid: %s line:%d\n",firstOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the first operand*/	
	two_operands_first(firstOpr,srcCodeLine);
	/*checks the meun for second operand*/
	if(is_meun_1(secondOpr)==FALSE &&is_meun_3(secondOpr)==FALSE)
	{
		printf("Error! the dest operand is invalid: %s line:%d\n",secondOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the second operand*/	
	two_operands_second(secondOpr,srcCodeLine);
}
/*This function creates word for clr action*/
void clr (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000101");
	strcpy(words.funct,"00001");
	clr_not_inc_dec_red (firstOpr,secondOpr,srcCodeLine);	
}
/*This function creates word for not action*/
void not (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000101");
	strcpy(words.funct,"00010");
	clr_not_inc_dec_red (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for inc action*/
void inc (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000101");
	strcpy(words.funct,"00011");
	clr_not_inc_dec_red (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for dec action*/
void dec (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"000101");
	strcpy(words.funct,"00100");
	clr_not_inc_dec_red (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for jmp action*/
void jmp (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"001001");
	strcpy(words.funct,"00001");
	jmp_bne_jsr (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for bne action*/
void bne (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"001001");
	strcpy(words.funct,"00010");
	jmp_bne_jsr (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for jsr action*/
void jsr (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"001001");
	strcpy(words.funct,"00011");
	jmp_bne_jsr (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for red action*/
void red (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"001100");
	strcpy(words.funct,"00000");
	clr_not_inc_dec_red (firstOpr,secondOpr,srcCodeLine);
}
/*This function creates word for prn action*/
void prn (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"001101");
	strcpy(words.funct,"00000");
	strcpy(words.meun_makor,"00");
	strcpy(words.oger_makor,"000");
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
	/*checks the meun for second operand*/
	if(is_meun_0(secondOpr)==FALSE &&is_meun_1(secondOpr)==FALSE &&is_meun_3(secondOpr)==FALSE)
	{
		printf("Error! the dest operand is invalid: %s line:%d\n",secondOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the second operand*/
	two_operands_second(secondOpr,srcCodeLine);
}
/*This function creates word for rts action*/
void rts (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"001110");
	strcpy(words.funct,"00000");
	strcpy(words.meun_makor,"00");
	strcpy(words.oger_makor,"000");
	strcpy(words.meun_yaad,"00");
	strcpy(words.oger_yaad,"000");
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
}
/*This function creates word for stop action*/
void stop (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.opcode,"001111");
	strcpy(words.funct,"00000");
	strcpy(words.meun_makor,"00");
	strcpy(words.oger_makor,"000");
	strcpy(words.meun_yaad,"00");
	strcpy(words.oger_yaad,"000");
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
}
/*This function checks the meun for operands of mov/ add/ sub actions*/
void mov_add_sub (char * firstOpr,char * secondOpr,int srcCodeLine)
{
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
	/*checks the meun for first operand*/
	if(is_meun_0(firstOpr)==FALSE &&is_meun_1(firstOpr)==FALSE &&is_meun_3(firstOpr)==FALSE)
	{
		printf("Error! the source operand is invalid: %s line:%d\n",firstOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the first operand*/
	two_operands_first(firstOpr,srcCodeLine);
	/*checks the meun for second operand*/
	if(is_meun_1(secondOpr)==FALSE &&is_meun_3(secondOpr)==FALSE)
	{
		printf("Error! the dest operand is invalid: %s line:%d\n",secondOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the second operand*/	
	two_operands_second (secondOpr,srcCodeLine);
}
/*This function checks the meun for operands of clr/ not/ inc/ dec/ red actions*/
void clr_not_inc_dec_red (char *firstOpr,char *secondOpr,int srcCodeLine)
{
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
	strcpy(words.meun_makor,"00");
	strcpy(words.oger_makor,"000");
	/*checks the meun for second operand*/
	if(is_meun_1(secondOpr)==FALSE &&is_meun_3(secondOpr)==FALSE)
	{
		printf("Error! the dest operand is invalid: %s line:%d\n",secondOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the second operand*/		
	two_operands_second(secondOpr,srcCodeLine);
}
/*This function checks the meun for operands of jmp/ bne/ jsr actions*/
void jmp_bne_jsr (char *firstOpr,char *secondOpr,int srcCodeLine)
{
	strcpy(words.A,"1");
	strcpy(words.R,"0");
	strcpy(words.E,"0");
	strcpy(words.meun_makor,"00");
	strcpy(words.oger_makor,"000");
	/*checks the meun for second operand*/
	if(is_meun_1(secondOpr)==FALSE &&is_meun_2(secondOpr)==FALSE)
	{
		printf("Error! the dest operand is invalid: %s line:%d\n",secondOpr,srcCodeLine);
		error=TRUE ;
	}
	/*continue create the word according to the meun of the second operand*/		
	two_operands_second(secondOpr,srcCodeLine);
}

