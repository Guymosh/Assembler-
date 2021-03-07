#include"header.h"
#include"structs.h"
/*This file contain function used for second round*/
int firstOprType=-1;/* -1 for no variable 0 for internal 1 for external 2 for number */
int secondOprType=-1;/* -1 for no variable 0 for internal 1 for external 2 for number 3 for distance*/
int dataAddress=100;
int codeAddress=100;
/*this function reads the source code and creates the words according to the information in each line */
void second_round (char* name,char* command,char* operands,char* firstOpr,char* secondOpr,char* zeros,char* ignore)
{
	extern int error;
	extern int codeLength;
	int i;
	int srcCodeLine=1;
	char* completeArray ;
	completeArray = (char*) calloc(MAX , sizeof(char));
	check_allocation(completeArray);
	dataAddress+=codeLength;
 	while(fscanf(fptr," %s ",command)==1)
  	{
	srcCodeLine++;
		/*if the new line contain entry the program will check if it exist in entry table and update the address of the label in the entry list*/
		while((strcmp(command,".entry")==0))
		{
			fgets ( command, sizeof command, fptr );
			if(is_entry (command)==TRUE)
				update_entry_symbol(command);
			if(fscanf(fptr," %s ",command)!=1) break;
				srcCodeLine++;
		}
		/*if the new line contain extern the program will ignore it */		
		while((strcmp(command,".extern")==0))
		{
			fgets ( ignore, sizeof ignore, fptr );
			if(fscanf(fptr," %s ",command)!=1) break;
				srcCodeLine++;	
		}
		/*if the new line contain comment the program will ignore it */	
		if(is_comment(command)==1)
		{	
			i=0;
			while(command[i]!='\0') i++;
			if (command[i-1]!='\n')
				fgets ( ignore, MAX, fptr );
			fscanf(fptr," %s ",command);
		}
		/*if the new line contain label the program will ignore it */	
		if(is_label(command)==1)
		{
			fscanf(fptr," %s ",command);
		}
		/*if the new line contain data the program will create data word */	
		if(strcmp(command,".data")==0)
		{
			create_data_word(command, completeArray,zeros);
		}
		/*if the new line contain string the program will create string words */	
		else if(strcmp(command,".string")==0)
		{
			create_string_word(command,completeArray);
		}
		/*if the new line contain action the program will create the first and second operands and the words according to the action and operands */	
		else
		{
			if(strcmp(command,".extern")!=0&&strcmp(command,".entry")!=0)
			{
				for(i=0; cmd[i].func!=NULL; i++)
				if (strcmp(cmd[i].name,command)==0)
					 break;
				if (cmd[i].func==NULL)continue;
				if(strcmp(command,"stop")!=0 && strcmp(command,"rts")!=0)
					/*create the first and second operands */
					create_operands(operands,firstOpr,secondOpr,zeros);
				/*create the word according the action */
				(*(cmd[i].func))(firstOpr,secondOpr,srcCodeLine);
				merge_arrays(completeArray,zeros);
				/*add the action word to the command list */
				add_command_list( completeArray, codeAddress);
				codeAddress++;
				/*if the first operand of the action required another word the program will create the word according to the type*/
				if(firstOprType==2||firstOprType==1||firstOprType==0)
				{
					if(firstOprType==1) /*external variable*/
					{
						add_extern_symbol(firstOpr,codeAddress);
						operand_externi();
						merge_arrays(completeArray,zeros);
					}
					else if(firstOprType==0) /*internal variable*/
					{
						operand_interni(1,completeArray,firstOpr,secondOpr);
					}
					else if(firstOprType==2) /*#NUMBER*/
					{
						operand_number(1,completeArray,firstOpr,secondOpr);
					}
				/*add the operand word to the command list */
				add_command_list( completeArray, codeAddress);
				firstOprType=-1;
				codeAddress++;
				}
				/*if the second operand of the action required another word the program will create the word according to the type*/
				if(secondOprType==3||secondOprType==2||secondOprType==1||secondOprType==0)
				{
					if(secondOprType==1) /*external variable*/
					{
						add_extern_symbol(secondOpr,codeAddress);
						operand_externi();
						merge_arrays(completeArray,zeros);
					}
					else if(secondOprType==0) /*internal variable*/
					{
						operand_interni(2,completeArray,firstOpr,secondOpr);
					}
					else if(secondOprType==2) /*#NUMBER*/
					{
						operand_number(2,completeArray,firstOpr,secondOpr);
					}
					else if(secondOprType==3) /*Distance*/
					{
						operand_distance(secondOpr,completeArray);
					}
				/*add the operand word to the command list */
				add_command_list( completeArray, codeAddress);
				secondOprType=-1;
				codeAddress++;
				}	
			}
		}
	}
	/*if there was no errors in source code during the run the program will create the files */
	if(error==FALSE)
	{
		print_command_list (name);
		write_entry_file(name);
		write_extern_file(name);
		fclose(object);
	}
	/*free allocated memory*/
	free(completeArray);
	
}
