#include"header.h"
/*This file contain functions used for create words according to the action or order*/

/*This function creates and adds to command list the words for data numbers*/
void create_data_word (char* command,char* completeArray,char* zeros)
{
	extern int dataAddress;
	int i;
	int number=0;
	int j=0;
	int *psikIndex;
	char *num;
	fscanf(fptr," %s ",command);
	psikIndex = (int*) calloc(MAX , sizeof(int));
	check_allocation(psikIndex);
	num = (char*) calloc(MAX , sizeof(char));
	check_allocation(num);
	for (i=0; command[i]!='\0';i++)
		if (command[i]==',')
		 {
			psikIndex[j]=i;
			j++;
		 }
	i=1;
	if(j==0) /*zero psiks-one number*/
   	{
		number=atoi (command);
		num_to_word(number,completeArray);
		add_command_list( completeArray, dataAddress);
		dataAddress++;
	}
	else
	{
		strncpy(num, command , psikIndex[0]); /* first number*/ 
		number=atoi (num);
		num_to_word(number,completeArray);
		add_command_list( completeArray, dataAddress);
		dataAddress++;
		while (i<j)	/*rest of numbers*/ 
		{
		 	strncpy(num, command + psikIndex[i-1]+1, psikIndex[i] - psikIndex[i-1]-1); 
			number=atoi (num);
			num_to_word(number,completeArray);
			add_command_list( completeArray, dataAddress);
			dataAddress++;
			i++;
			strcpy(num,zeros);
		}
		strncpy(num, command +psikIndex[j-1]+1, strlen(command)-psikIndex[j-1]); /* last number*/
		number=atoi (num);
		num_to_word(number,completeArray);
		add_command_list( completeArray, dataAddress);
		dataAddress++;
	}
	free(psikIndex);
	free(num);	
}
/*This function creates and adds to command list the words for string letters*/
void create_string_word (char * command,char* completeArray)
{
	extern int dataAddress;
	fscanf(fptr," %s ",command);
	remove_char(command, '\n');
	remove_char(command, '"');
	while (*command!='\0')
	{
		strcpy(completeArray,letter_to_word(*command,completeArray));
		add_command_list( completeArray, dataAddress);
		dataAddress++;
		command++;
	}
	strcpy(completeArray,letter_to_word('\0',completeArray));
	add_command_list( completeArray, dataAddress);
	dataAddress++;
}

/*This function create and return the distance word between action and label*/
void operand_distance (char* secondOpr,char* completeArray) 
{
	extern symbol * head;
	int delta;
	extern int codeAddress;
	symbol *ptr = head;
	remove_char(secondOpr, '&');
	while (ptr)
	{
	    if (strcmp(ptr->label, secondOpr)==0)
	    {
		delta=ptr->labelAddress;
		break;
	    }
	    ptr = ptr->next;
	}
	delta=delta-(codeAddress-1);
	/*move 3 spots to the left and add '100' to the word*/
	delta*=8;
	delta+=4;
	num_to_word(delta,completeArray);
}
/*This function create and return the word for #NUMBER operand*/
void operand_number (int index,char* completeArray,char* firstOpr,char* secondOpr) /*index=1 for first operand index=2 for secondoperand */
{
	int num;
	remove_char(firstOpr, '#');
	remove_char(secondOpr, '#');
	if(index==1) num=atoi (firstOpr);
	else if(index==2) num=atoi (secondOpr);
	/*move 3 spots to the left and add '100' to the word*/
	num*=8;
	num+=4;
	num_to_word(num,completeArray);	
}

/*This function create and return the address word for internal parameter*/
void operand_interni (int num,char* completeArray,char* firstOpr,char* secondOpr) /*num=1 for first operand num=2 for secondoperand */
{	
	extern  symbol * head;
	int address;
	char* str;
	symbol *ptr = head;
	if(num==1)str=firstOpr; 
	else if(num==2)str=secondOpr;
	while (ptr)
	{
	    if (strcmp(ptr->label, str)==0)
	    {
		address=ptr->labelAddress;
		break;
	    }
	    ptr = ptr->next;
	}
	/*move 3 spots to the left and add '010' to the word*/
	address*=8;
	address+=2;
	num_to_word(address,completeArray);
}
/*This function creates word for extern operand */
void operand_externi (void)
{	
	strcpy(words.opcode,"000000");
	strcpy(words.funct,"00000");
	strcpy(words.meun_makor,"00");
	strcpy(words.oger_makor,"000");
	strcpy(words.meun_yaad,"00");
	strcpy(words.oger_yaad,"000");
	strcpy(words.A,"0");
	strcpy(words.R,"0");
	strcpy(words.E,"1");
}
/*This function fills the first operand's meun and oger areas in the word */
void two_operands_first (char *firstOpr,int srcCodeLine)
{
	extern int firstOprType;/* -1 for no variable 0 for internal 1 for external 2 for number  */
	if(is_meun_1(firstOpr)==TRUE)
	{		
		strcpy(words.meun_makor,"01");
		strcpy(words.oger_makor,"000");	
		if(is_extern (firstOpr)==TRUE) firstOprType=1;
		else firstOprType=0;
	}
	else if(is_meun_3(firstOpr)==TRUE)
	{		
		strcpy(words.meun_makor,"11"); 
		strcpy(words.oger_makor,r_number(firstOpr));
	}
	else /*if (is_meun_0(firstOpr)==TRUE)*/
	{
		firstOprType=2;
		strcpy(words.meun_makor,"00");
		strcpy(words.oger_makor,"000");
	}
}
/*This function fills the second operand's meun and oger areas in the word */
void two_operands_second (char *secondOpr,int srcCodeLine)
{
	extern int secondOprType;/* -1 for no variable 0 for internal 1 for external 2 for number 3 for distance */
	if(is_meun_1(secondOpr)==TRUE)
	{
		strcpy(words.meun_yaad,"01");
		strcpy(words.oger_yaad,"000");	
		if(is_extern (secondOpr)==TRUE) secondOprType=1;
		else secondOprType=0;
	}
	else if(is_meun_2(secondOpr)==TRUE)
	{
		secondOprType=3;
		strcpy(words.meun_yaad,"10");
		strcpy(words.oger_yaad,"000");
	}
	else if(is_meun_3(secondOpr)==TRUE)
	{
		strcpy(words.meun_yaad,"11");
		strcpy(words.oger_yaad,r_number(secondOpr)); 

	}
	else /*if (is_meun_0(secondOpr)==TRUE)*/
	{
		secondOprType=2;
		strcpy(words.meun_yaad,"00");
		strcpy(words.oger_yaad,"000");	
	}
}





