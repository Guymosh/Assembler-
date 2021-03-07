#include"header.h"
/*This file contain functions used for checking different parametes*/

/*This function checks if given string is number*/
int is_number (char* str)
{
	int plusCount=0;
	int minusCount=0;
	char c;	
	if(str ==NULL||*str=='\0') 
		return FALSE;
	while (*str!='\n' && *str!='\0')
	{
		c =*str;
		switch (c)
		{
			case '-':
				if(++minusCount>1) return FALSE;
				break;
			case '+':
				if(++plusCount>1) return FALSE;
				break;
			default :
				if(c<'0'||c>'9') return FALSE;
		}
		str++;
	}
	return TRUE;	
}
/*This function checks if given operand is meun-miyadi*/
int is_meun_0 ( char* operand)
{
	if (operand[0]!='#') return FALSE;
	operand++;
	return is_number (operand);
}
/*This function checks if given operand is meun-yashir*/
int is_meun_1 (char* operand)
{	
	if(is_labelist(operand)==1) return TRUE; 
	else return FALSE;
}
/*This function checks if given operand is meun-yahasi*/
int is_meun_2 (char* operand)
{
	if(operand[0]!='&') return FALSE;
	operand++;
	if(is_labelist(operand)==1) return TRUE; 
	else return FALSE;
}
/*This function checks if given operand is meun-oger-yashir*/
int is_meun_3 ( char* operand)
{
	if(operand[0]!='r') 
		return FALSE;
	if(operand[1]!='0'&&operand[1]!='1'&&operand[1]!='2'&&operand[1]!='3'&&operand[1]!='4'&&operand[1]!='5'&&operand[1]!='6'&&operand[1]!='7')
		return FALSE;
	if(operand[2]=='\0' || operand[2]=='\n') 
		return TRUE;	
	else return FALSE;
}
/*This function checks if given operand exists in the label list*/
int is_labelist ( char *str)
{
	extern  symbol * head;
  	symbol *ptr = head;
	while (ptr)
	{
	    if (strcmp(ptr->label, str)==0)
	    {
	      return TRUE;
	    }
	    ptr = ptr->next;
	}
	return FALSE;	
}
/*This function checks if given operand exists in the entry label list*/
int is_entry ( char *str)
{
	extern  entrySymbol * entryHead;
	entrySymbol *ptr = entryHead;
	remove_char(str, '\n');
	while (ptr)
	{
	    if (strcmp(ptr->entryTable, str)==0)
	    {
			return TRUE;		
	    }
	    ptr = ptr->next;
	}
	return FALSE;
}
/*This function checks if given operand exists in the label list and signed as extern*/
int is_extern ( char *str)
{
	extern  symbol * head;
	symbol *ptr = head;
	while (ptr)
	{
	    if (strcmp(ptr->label, str)==0)
	    {
		if(ptr->externy==TRUE)
		{
			return TRUE;		
		}

	    }
	    ptr = ptr->next;
	}
	return FALSE;	
}
/*This function checks if given string is label*/
int is_label ( char *str)
{
	int i=0;
	while(str[i]!='\0') i++;
	if (str[i-1]==':') return TRUE;
	else return FALSE;
}
/*This function checks if given string is comment*/
int is_comment (char *str)
{
	if (str[0]==';') return TRUE;
	else return FALSE;
}
/*This function return given dec char number as binary string number*/
char * r_number (char* operand)
{	
	if(operand[1]=='0') return "000";
	if(operand[1]=='1') return "001";
	if(operand[1]=='2') return "010";
	if(operand[1]=='3') return "011";
	if(operand[1]=='4') return "100";
	if(operand[1]=='5') return "101";
	if(operand[1]=='6') return "110";
	if(operand[1]=='7') return "111";
	return "999";
}
/*This function checks if pointer is null*/
void check_allocation(void * ptr)
{
	extern int error;
	if (!ptr)
	{
	    printf("The program has quit due to a memory allocation error.\n");
	    error=TRUE;
	}
}
/*This function checks if given string contains psiks*/
int check_psik(char *str) 
{
    char *src;
    for (src = str; *src != '\0'; src++) 
    {
        if (*src == ',') 
		return TRUE;
    }
    return FALSE;
}

