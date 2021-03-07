#include "header.h"
/*This file contains functions used for file handling*/

/*openFile function - used to open files.
  takes 3 strings - filename, mode and extension.
  returns a pointer to the opened file, or null if failed*/
FILE * openFile(char* filename, char * mode, char * extension)
{
  /*Temp file to be returned*/
  FILE * tmp = NULL;
  char full_filename[MAX];
  strcpy(full_filename, filename);
  strcat(full_filename, extension);
  /*Open the file. if fopen return null, exit the function and print error to screen*/
  if (!(tmp = fopen(full_filename, mode)))
  {
    printf("Can't open file %s.\n", full_filename);
    return NULL;
  }
  /*Return pointer to the file*/
  return tmp;
}
/*This function creates extern file and write into it the extern table*/
void write_extern_file (char* name)
{	
	extern  FILE * externals;
	extern externSymbol * externHead;
	externSymbol *ptr = externHead;
   	/* Checking for empty list */
   	if (ptr == NULL) 
      		  return; 
	/*open an extern file in write mode*/
	externals = openFile(name, "w", ".ext");
	while (ptr)
	{
		fprintf(externals,"%s %d \n", ptr->externTable, ptr->externAddress );
	 	ptr = ptr->next;
	}
	fclose(externals);
}
/*This function creates entry file and write into it the entry table*/
void write_entry_file (char* name)
{
	extern  entrySymbol * entryHead;	
	extern  FILE * entries;
	entrySymbol *ptr = entryHead;
   	/* Checking for empty list */
   	if (ptr == NULL) 
      		  return; 
	/*open an entries file in write mode*/			
	entries = openFile(name, "w", ".ent");
	entry_bubble_sort(entryHead);
	while (ptr)
	{  
		fprintf(entries,"%s  %d \n",ptr->entryTable, ptr->entryAddress );
		ptr = ptr->next;
	}
	fclose(entries);
}
/*This function creates object file and write into it the command list*/
void print_command_list (char *name)
{
	extern int dataLength;
	extern int codeLength;
	extern commandList * cmdHead;
 	commandList *ptr = cmdHead;
	/*open an object file in write mode*/
	object = openFile(name, "w", ".ob");
	fprintf(object, "%d %d\n", codeLength, dataLength);
	command_bubble_sort(cmdHead);
	while (ptr)
	{
		fprintf(object,"%d  %X \n", ptr->line,create_hex_word (ptr->completeArray) );
	   	ptr = ptr->next;
	}

}


