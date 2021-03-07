#include"header.h"
/*This file contains functions used for different operations required in the program*/

/*This function creates the word in machine lenguage*/
void merge_arrays (char * completeArray,char *zeros)
{
	strcpy(completeArray,zeros);
	strcat(completeArray,words.opcode);
	strcat(completeArray,words.meun_makor);
	strcat(completeArray,words.oger_makor);
	strcat(completeArray,words.meun_yaad);
	strcat(completeArray,words.oger_yaad);
	strcat(completeArray,words.funct);
	strcat(completeArray,words.A);
	strcat(completeArray,words.R);
	strcat(completeArray,words.E);

}
/*This function gets a string and divid it to first and second operands*/
void create_operands (char* operands,char* firstOpr,char* secondOpr,char* zeros )
{
	fgets ( operands, MAX, fptr );
	remove_char(operands, '\n');
	remove_char(operands, '\t');
	remove_char(operands, ' ');
	first_operand(operands, firstOpr,zeros);
	second_operand(operands, secondOpr);
}
/*This function create the first operand */
void first_operand (char* operands,char* firstOpr,char* zeros)
{
	int i = 0;
	int flag=FALSE;
	strcpy(firstOpr,zeros);
	for(i=0;operands[i]!='\0';i++)
		if (operands[i]==',') 
		{
			flag=TRUE; 
			break;
		}
	if(flag==TRUE)
	strncpy(firstOpr, operands , i);
	firstOpr[i]='\0';	
}
/*This function create the second operand */
void second_operand (char* operands,char* secondOpr)
{
	int i,j;
	int psikIndex=-1;
	int length=sizeof(operands);
	for(i=0;operands[i]!='\0';i++)
		if ((operands[i]==',') && (psikIndex==-1))
			psikIndex=i; 
	j=0;
	while(j<length)
	{
		secondOpr[j]=operands[psikIndex+j+1];
		j++;
	}
	secondOpr[j]='\0';
}
/*This function checks how many numbers are in a given string */
int how_many_numbers (char* command,char* zeros)
{
	int *psikIndex;	
	char *num;
	int i;
	int j=0;
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
	if(j==0) /*zero psiks*/
	   	{
  		   	if(is_number(command)==TRUE) return 1;
			return -1;
		}
	strncpy(num, command , psikIndex[0]); /*checking first number*/ 
	if(is_number(num)==FALSE) 
		return -1;
	strncpy(num, command +psikIndex[j-1]+1, strlen(command)-psikIndex[j-1]); /*checking last number*/
	if(is_number(num)==FALSE) 
		return -1;
	while (i<j)	/*checking rest of numbers*/
	{
	 	strncpy(num, command + psikIndex[i-1]+1, psikIndex[i] - psikIndex[i-1]-1);  
		if(strcmp(num,zeros)==0) return -1;
		if(is_number(num)==FALSE) return -1;
		i++;
		strcpy(num,zeros);
	}
	free(psikIndex);
	free(num);
	return j+1;
}
/*This function translate letter to binary word and returns it*/
char* letter_to_word(char letter,char* completeArray)
{
	int letterval=letter;
	num_to_word(letterval,completeArray);
	return completeArray;
}
/*This function translate dec number to binary word */
void num_to_word (int num,char *completeArray)
{
	int *a;
	int i;
	int j;
	int flag=FALSE;
	a = (int*) calloc(MAX , sizeof(int));
	check_allocation(a);
	if(num>=0)
	{
		for(i=0;num>0;i++)    
		{    
			a[i]=num%2;    
			num=num/2; 	   
		}  
		for(j=0;j<SIZE-i;j++)
		{
			*completeArray='0';
			completeArray++;
		}
		for(i=i-1;i>=0;i--)    
		{  
			if (a[i]==0)*completeArray='0';
			else *completeArray='1';
			completeArray++;      
		}
	}
	else
	{
		num*=(-1);
		for(i=0;num>0;i++)    
		{    
			a[i]=num%2;    
			num=num/2;    
		}  
		for (j=0;j<i;j++)
		{
			if(a[j]==1 && flag==FALSE)
				flag=TRUE;
			else if(a[j]==0 && flag==TRUE) 
				a[j]=1;
			else if(a[j]==1 && flag==TRUE) 
				a[j]=0;
		}
		for(j=0;j<SIZE-i;j++)
		{
			*completeArray='1';
			completeArray++;
		}

		for(i=i-1;i>=0;i--)    
		{  
			if (a[i]==0)
				*completeArray='0';
			else *completeArray='1';
			completeArray++;      
		}
	}
	*completeArray='\0';
	completeArray-=SIZE;
	free(a);
}
/*This function remove a given char from a given string*/
void remove_char(char *str, char garbage) 
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) 
    {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

/*This function creates and returns the word in hex value*/
int create_hex_word (char *completeArray)
{
	char *a = completeArray;
	int num = 0;
	do 
	{
	    int b = *a=='1'?1:0;
	    num = (num<<1)|b;
	    a++;
	} while (*a);
	return num;
}



