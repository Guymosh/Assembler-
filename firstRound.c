#include"header.h"
#include"structs.h"
/*This file contain function used for first round*/
int codeLength=100;
int dataLength=0;
int ic=100;
int dc=0;
int error=FALSE;
/*this function creates the table list , the code length and the data length, and rints errors if the code is incorrect */
void first_round (char* command,char* operands,char* firstOpr,char* secondOpr,char* zeros,char* ignore)
{
  int srcCodeLine=1;
  char* label;
  int i;			
  int countNumbers;	
  while(fscanf(fptr," %s ",command)==1)
  {
  	srcCodeLine++;
  	label = (char*) calloc(MAX , sizeof(char));
  	check_allocation(label);
	/*if the new line is comment the program ignore it*/
	if(is_comment(command)==1)
	{	
		i=0;
		while(command[i]!='\0') i++;
		if (command[i-1]!='\n')
			fgets ( ignore, MAX, fptr );
		fscanf(fptr," %s ",command);
	}
	/*if the new line contains label the program will add it to table list*/
	if(is_label(command)==1)
	{
		check_symbol(command); /*checks if the symbol is already in the table list*/
		strcpy(label,command);
		fscanf(fptr," %s ",command);
		if(strcmp (command,".data")==0||strcmp(command,".string")==0)
		{
			add_symbol( label, dc, FALSE, FALSE);
		}
		else if (strcmp (command,".extern")==0||strcmp (command,".entry")==0)
		{
			printf(".extern or .entry cannot appear after label! line:%d \n",srcCodeLine);
			error=TRUE ;	
		}
		else
		{	
			for(i=0; cmd[i].func!=NULL; i++)
			if (strcmp(cmd[i].name,command)==0)
				break;
			if (cmd[i].func!=NULL) 
			{	
				add_symbol( label, ic, FALSE, TRUE);
			}
		}
	}
	/*if the new line contains an order the program will count the dc*/
	if(strcmp (command,".data")==0||strcmp(command,".string")==0)	
	{
		if(strcmp(command,".string")==0)
		{
			fgets ( command, sizeof command, fptr );
			if(command[0]!='"'||command[strlen(command)-2]!='"') 
			{
				printf("the string define is incorrect! line:%d \n",srcCodeLine);
				error=TRUE  ;					
			}				
			dc+=(strlen(command)-2);	
		}
		if(strcmp(command,".data")==0)
		{
			fgets ( command, sizeof command, fptr );
			countNumbers= how_many_numbers(command,zeros);
			if (countNumbers==-1) 
			{
				printf("the number define is incorrect! line:%d \n",srcCodeLine);
				error=TRUE  ;
			}
			dc+=countNumbers; 
		}
	}
	/*if the new line contains an extern or entry order the program will add it to table list or to entry table list accordingly*/
	else if(strcmp (command,".extern")==0||strcmp (command,".entry")==0)
	{
		if(strcmp(command,".extern")==0)
		{
			fgets ( command, sizeof command, fptr );
			remove_char(command, '\n');
			add_symbol(command, 0, TRUE, FALSE);
		}
		if(strcmp(command,".entry")==0)
		{
			fgets ( command, sizeof command, fptr );
			remove_char(command, '\n');
			add_entry_symbol(command,0);
		}	
	}
	/*if the new line contains an action the program will create the first and second operands and count the ic */
	else
	{
		for(i=0; cmd[i].func!=NULL; i++)
		if (strcmp(cmd[i].name,command)==0)
			break;
		if (cmd[i].func==NULL)
		{
			printf("Command does not exist: %s line:%d\n",command,srcCodeLine);
			fgets ( ignore, sizeof ignore, fptr );
			error=TRUE  ;
		}
    	  	else /*count ic*/
	  	{
		ic++;
			
			if(strcmp (command,"mov")==0||strcmp (command,"cmp")==0||strcmp (command,"add")==0||strcmp(command,"sub")==0||strcmp(command,"lea")==0)	
			{	
				create_operands(operands,firstOpr,secondOpr,zeros);
				if(strcmp (firstOpr,zeros)==0||strcmp (secondOpr,zeros)==0) 
				{
					 printf("Error! at least two operands required: firstOpr:%s secondOpr:%s line:%d\n",firstOpr,secondOpr,srcCodeLine);
					 error=TRUE  ;
				}
				if(check_psik(firstOpr)==TRUE||check_psik(secondOpr)==TRUE) 
				{
					 printf("Error! too many psiks! line:%d\n",srcCodeLine);
					 error=TRUE  ;
				}
				if(is_meun_3(firstOpr)==FALSE)
					ic++;
				if(is_meun_3(secondOpr)==FALSE)
					ic++;
			}
			else if(strcmp (command,"clr")==0||strcmp (command,"not")==0||strcmp (command,"inc")==0||strcmp(command,"dec")==0||strcmp(command,"jmp")==0||strcmp(command,"bne")==0||strcmp(command,"jsr")==0||strcmp(command,"red")==0||strcmp(command,"prn")==0)	
			{
				create_operands(operands,firstOpr,secondOpr,zeros);
				if(strcmp (firstOpr,zeros)!=0) 
				{
					 printf("Error! too many operands: firstOpr:%s secondOpr:%s line:%d\n",firstOpr,secondOpr,srcCodeLine);
					 error=TRUE  ;
				}
				if(check_psik(operands)==TRUE) 
				{
					 printf("Error! too many psiks! line:%d\n",srcCodeLine);
					 error=TRUE  ;
				}			
				if(is_meun_3(secondOpr)==FALSE)
					ic++;			
			}			
	  	}
	}


  }
  /*update the table list for orders with dc counter*/
  update_symbols(ic); 
  /*create the code length and data length*/
  codeLength=ic-codeLength;
  dataLength=dc;
  /*free allocated memory*/	
  free(label);

}

