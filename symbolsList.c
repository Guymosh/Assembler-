#include "header.h"
/*This file contain functions used for add update or free the differnet structures in the program*/

/*Pointers to structure heads*/
symbol * head = NULL;
entrySymbol * entryHead = NULL;
commandList * cmdHead= NULL;
externSymbol * externHead = NULL;

/*This function adds a symbol to the symbols list*/
void add_symbol(char * label, int labelAddress, int externy, int action)
{
  /*Temp sybol*/
  symbol * tmp = NULL;
  tmp = malloc(sizeof(symbol));
  check_allocation(tmp);
  tmp->label = malloc(sizeof(char)*MAX);
  check_allocation(tmp->label);
  remove_char(label, ':');
  /*Copy the label from the input to this symbol*/
  strcpy(tmp->label, label);
  /*Copy value of DC*/
  tmp->labelAddress = labelAddress;
  /*Copy externy flag*/
  tmp->externy = externy;
  /*Copy action tab*/
  tmp->action = action;
  tmp->next = NULL;
  /*if list is empty*/
  if (!head)
  {
    /*make head point to temp*/
    head = tmp;
  }
  /*if list isn't empty*/
  else
  {
    /*create pointer to head*/
    symbol * p = head;
    /*get to the last node*/
    while (p->next)
      p = p->next;
    /*set last node's next to tmp*/
    p->next = tmp;
  }
}
/*This function will update the symbol's addresses to match with the IC counter, after the first pass*/
void update_symbols(int ic)
{
  symbol * ptr = head;
  while (ptr)
  {
    if ((ptr->externy == FALSE) && (ptr->action == FALSE))
    {
      ptr->labelAddress += ic;
    }
    ptr = ptr->next;
  }
}
/*This function cleans up the symbol list*/
void free_symbols()
{
  symbol * ptr = head;
  if (!ptr)
    return;
  while (ptr)
  {
      symbol * tmp = ptr;
      ptr = ptr->next;
      free(tmp->label);
      free(tmp);
  }
  head = NULL;
}
/*This function checks if a symbol with the same name exists*/
void check_symbol(char * label)
{
  symbol * ptr = head;
  while (ptr)
  {
    if (!strcmp(ptr->label, label))
    {
      printf("cant use same name of label twice! label: %s \n", label);
      return;
    }
    ptr = ptr->next;
  }
}
/*This function adds a symbol to the entry list*/
void add_entry_symbol(char * entryTable,int entryAddress)
{
  /*Temp entrySymbol*/
  entrySymbol * tmp = NULL;
  tmp = malloc(sizeof(entrySymbol));
  check_allocation(tmp);
  tmp->entryTable = malloc(sizeof(char)*MAX);
  check_allocation(tmp->entryTable);
  /*Copy the label from the input to this entrySymbol*/
  strcpy(tmp->entryTable, entryTable);
  /*Copy entryAddress*/
  tmp->entryAddress = entryAddress;
  /*set next to NULL*/
  tmp->next = NULL;
  /*if list is empty*/
  if (!entryHead)
  {
    /*make head point to temp*/
    entryHead = tmp;
  }
  /*if list isn't empty*/
  else
  {
    /*create pointer to head*/
    entrySymbol * p = entryHead;
    /*get to the last node*/
    while (p->next)
      p = p->next;
    /*set last node's next to tmp*/
    p->next = tmp;
  }
}
/*This function cleans up the entry list*/
void free_entry_symbols()
{
  entrySymbol * ptr = entryHead;
  if (!ptr)
    return;
  while (ptr)
  {
      entrySymbol * tmp = ptr;
      ptr = ptr->next;
      free(tmp->entryTable);
      free(tmp);
  }
  entryHead = NULL;
}
/*This function cleans up the command list*/
void free_command_list()
{
  commandList * ptr = cmdHead;
  if (!ptr)
    return;
  while (ptr)
  {
      commandList * tmp = ptr;
      ptr = ptr->next;
      free(tmp->completeArray);
      free(tmp);
  }
  cmdHead = NULL;
}
/*This function adds a symbol to the command list*/
void add_command_list(char * completeArray, int line)
{
  /*Temp commandList*/
  commandList * tmp = NULL;
  tmp = malloc(sizeof(commandList));
  check_allocation(tmp);
  tmp->completeArray = malloc(sizeof(char)*MAX);
  remove_char(completeArray, '!');
  check_allocation(tmp->completeArray);
  /*Copy the word from the input to this commandList*/
  strcpy(tmp->completeArray, completeArray);
  /*Copy value of line*/
  tmp->line = line;
  /*set next to NULL*/
  tmp->next = NULL;
  /*if list is empty*/
  if (!cmdHead)
  {
    /*make head point to temp*/
    cmdHead = tmp;
  }
  /*if list isn't empty*/
  else
  {
    /*create pointer to head*/
    commandList * p = cmdHead;
    /*get to the last node*/
    while (p->next)
      p = p->next;
    /*set last node's next to tmp*/
    p->next = tmp;
  }
}
/*This function adds a symbol to the extern list*/
void add_extern_symbol(char * externTable,int externAddress)
{
  /*Temp externSymbol*/
  externSymbol * tmp = NULL;
  tmp = malloc(sizeof(externSymbol));
  check_allocation(tmp);
  tmp->externTable = malloc(sizeof(char)*MAX);
  check_allocation(tmp->externTable);
  remove_char(externTable, '\n');
  /*Copy the label from the input to this externSymbol*/
  strcpy(tmp->externTable, externTable);
  /*Copy externAddress*/
  tmp->externAddress = externAddress;
  /*set next to NULL*/
  tmp->next = NULL;
  /*if list is empty*/
  if (!externHead)
  {
    /*make head point to temp*/
    externHead = tmp;
  }
  /*if list isn't empty*/
  else
  {
    /*create pointer to head*/
    externSymbol * p = externHead;
    /*get to the last node*/
    while (p->next)
      p = p->next;
    /*set last node's next to tmp*/
    p->next = tmp;
  }
}
/*This function cleans up the extern list*/
void free_extern_symbols()
{
  externSymbol * ptr = externHead;
  if (!ptr)
    return;
  while (ptr)
  {
      externSymbol * tmp = ptr;
      ptr = ptr->next;
      free(tmp->externTable);
      free(tmp);
  }
  externHead = NULL;
}
/*This function update the address of given label in the entry list*/
void update_entry_symbol (char* command)
{
	extern  symbol * head;	
	extern  entrySymbol * entryHead;
	int tmp =0;
	symbol *ptr = head;
	entrySymbol *p = entryHead;
	remove_char(command, '\n');
	while (ptr)
	{
	    if (strcmp(ptr->label, command)==0)
	    {
		tmp= ptr->labelAddress; 
	    }
	    ptr = ptr->next;
	}
	while (p)
	{
	    if (strcmp(p->entryTable, command)==0)
	    {
		p->entryAddress=tmp; 
	    }
	    p = p->next;
	}		
}
/* Bubble sort according to address to the entry list */
void entry_bubble_sort(struct entrySymbol *start) 
{ 
    int swapped; 
    struct entrySymbol *ptr1; 
    struct entrySymbol *lptr = NULL; 
    /* Checking for empty list */
    if (start == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        ptr1 = start; 
        while (ptr1->next != lptr) 
        { 
            if (ptr1->entryAddress > ptr1->next->entryAddress) 
            {  
                entry_swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } while (swapped); 
} 
/* function to swap data of two entry symbols a and b*/
void entry_swap(struct entrySymbol *a, struct entrySymbol *b) 
{ 
    int tempAdrress = a->entryAddress; 
    char * tempLabel = a->entryTable;
    a->entryAddress = b->entryAddress; 
    b->entryAddress = tempAdrress; 
    a->entryTable = b->entryTable; 
    b->entryTable = tempLabel;
}
/* Bubble sort according to address to the command list */
void command_bubble_sort(struct commandList *start) 
{ 
    int swapped; 
    struct commandList *ptr1; 
    struct commandList *lptr = NULL; 
    /* Checking for empty list */
    if (start == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        ptr1 = start; 
        while (ptr1->next != lptr) 
        { 
            if (ptr1->line > ptr1->next->line) 
            {  
                command_swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } while (swapped); 
}  
/* function to swap data of two nodes in the command List a and b*/
void command_swap(struct commandList *a, struct commandList *b) 
{ 
    int tempAddress = a->line; 
    char * tempLabel = a->completeArray;
    a->line = b->line; 
    b->line = tempAddress; 
    a->completeArray = b->completeArray; 
    b->completeArray = tempLabel;
}

