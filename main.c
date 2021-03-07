
#include"header.h"
/*Pointers to input file*/
FILE * fptr = NULL;
FILE * object = NULL;
FILE * entries = NULL;
FILE * externals = NULL;
int main (int argc, char* argv[])
{
  char* command;
  char* operands;
  char* firstOpr;
  char* secondOpr;
  char* zeros;
  char* ignore;
  /*Index used to loop through the input files*/
  int index;
  /*Check if there are no arguments*/
  if (argc == 1)
  {
    /*Print error to screen*/
    printf("You did not provide any input files.\n");
  }
  else
  {
    /*Loop which goes through all of argv's elements*/
    for (index = 1; index < argc; index++)
    {
      printf("%s.as: \n", argv[index]);
      /*Open the file and do everything*/
      if ((fptr = openFile(argv[index], "r", ".as")))
      {
	/*allocate memory to all the strings the program will use*/	
	command = (char*) calloc(MAX , sizeof(char));
	check_allocation(command);
	operands = (char*) calloc(MAX , sizeof(char));
	check_allocation(operands);
	firstOpr = (char*) calloc(MAX , sizeof(char));
	check_allocation(firstOpr);
	secondOpr = (char*) calloc(MAX , sizeof(char));
	check_allocation(secondOpr);
	zeros = (char*) calloc(MAX , sizeof(char));
	check_allocation(zeros);
	ignore = (char*) calloc(MAX , sizeof(char));
	check_allocation(ignore);
	/*starting first round*/
	first_round(command,operands,firstOpr,secondOpr,zeros,ignore);
	/*reopen for the second round*/
	fclose(fptr);
	fptr = openFile(argv[index], "r", ".as");
	/*starting second round*/
	second_round(argv[index],command,operands,firstOpr,secondOpr,zeros,ignore);
	/*free all allocated memory*/
	free(ignore);
	free(zeros);
	free (command);
	free (operands);
	free (firstOpr);
	free (secondOpr);
	fclose(fptr);
	free_symbols();
	free_entry_symbols();
	free_extern_symbols();
	free_command_list();
       }
    }
  }


return 0;
}









