
#define MAX 100
#define SIZE 24
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
enum {FALSE,TRUE};
FILE *fptr;
FILE * object; 
FILE * entries;
FILE * externals;

/*files.c*/
FILE * openFile(char* filename, char * mode, char * extension);
void write_extern_file (char* name);
void write_entry_file (char* name);
void print_command_list (char* name);

/*firstRound.c*/
void first_round (char* command,char* operands,char* firstOpr,char* secondOpr,char* zeros,char* ignore);

/*secondRound.c*/
void second_round (char* name,char* command,char* operands,char* firstOpr,char* secondOpr,char* zeros,char* ignore);

/*operations.c*/
void  merge_arrays (char *,char*zeros);
void create_operands (char* operands,char* firstOpr,char* secondOpr,char* zeros );
void first_operand (char* operands,char* firstOpr,char* zeros);
void second_operand (char* operands,char* secondOpr);
int how_many_numbers (char* str,char* zeros);
void num_to_word (int num,char *completeArray);
char* letter_to_word(char letter,char *completeArray);
void remove_char(char *str, char garbage) ;
int create_hex_word (char *completeArray);


/*createWord.c*/
void mov (char * firstOpr,char * secondOpr,int srcCodeLine);
void cmp (char * firstOpr,char * secondOpr,int srcCodeLine);
void add (char * firstOpr,char * secondOpr,int srcCodeLine);
void sub (char * firstOpr,char * secondOpr,int srcCodeLine);
void lea (char * firstOpr,char * secondOpr,int srcCodeLine);
void clr (char * firstOpr,char * secondOpr,int srcCodeLine);
void not (char * firstOpr,char * secondOpr,int srcCodeLine);
void inc (char * firstOpr,char * secondOpr,int srcCodeLine);
void dec (char * firstOpr,char * secondOpr,int srcCodeLine);
void jmp (char * firstOpr,char * secondOpr,int srcCodeLine);
void bne (char * firstOpr,char * secondOpr,int srcCodeLine);
void jsr (char * firstOpr,char * secondOpr,int srcCodeLine);
void red (char * firstOpr,char * secondOpr,int srcCodeLine);
void prn (char * firstOpr,char * secondOpr,int srcCodeLine);
void rts (char * firstOpr,char * secondOpr,int srcCodeLine);
void stop (char * firstOpr,char * secondOpr,int srcCodeLine);
void mov_add_sub (char * firstOpr,char * secondOpr,int srcCodeLine);
void clr_not_inc_dec_red (char *firstOpr,char *secondOpr,int srcCodeLine);
void jmp_bne_jsr (char *firstOpr,char *secondOpr,int srcCodeLine);

/*checks.c*/
int is_entry ( char *str);
int is_extern ( char *str);
char * r_number (char* );
int is_meun_0 ( char str[]);
int is_meun_1 (char* str);
int is_meun_2 (char *str);
int is_meun_3 (char *str);
int is_labelist ( char *str);
int is_label ( char *str);
int is_number (char* str);
int is_comment ( char *str);
void check_allocation(void * ptr);
int check_psik(char *str) ;


 struct word
{
    char A[2];
    char R[2];
    char E[2];
    char opcode[7];
    char funct[6];
    char meun_yaad[3];
    char meun_makor[3];
    char oger_yaad[4];
    char oger_makor[4];
}words;



/*definition of symbol type
contains a string (label),
address, and externy/action flags*/
typedef struct symbol
{
  /*Label of the symbol*/
  char * label;
  /*Address of the symbol*/
  int labelAddress;
  /*TRUE for extern FALSE for internal*/
  int externy;
  /*TRUE for action FALSE for order*/
  int action;
  /*pointer to next*/
  struct symbol * next;
} symbol;

/*definition of entrySymbol type
contains a string (label),
address */
typedef struct entrySymbol
{
  /*Label of the symbol*/
  char * entryTable;
  /*address of command*/
  int entryAddress;
  /*pointer to next*/
  struct entrySymbol * next;
} entrySymbol;

/*definition of externSymbol type
contains a string (label),
address */
typedef struct externSymbol
{
  /*Label of the symbol*/
  char * externTable;
  /*address of command*/
  int externAddress;
  /*pointer to next*/
  struct externSymbol * next;
} externSymbol;

/* */
typedef struct commandList
{
  /*word of command in machine lenguage*/
  char * completeArray;
  /*address of command*/
  int line;
  /*pointer to next*/
  struct commandList * next;
} commandList;

/*symbolsList.c*/
void update_symbols(int ic);
void free_symbols();
void check_symbol(char * label);
void add_symbol(char * label, int labelAddress, int externy, int action);
void free_entry_symbols();
void add_entry_symbol(char * entryTable,int );
void free_command_list();
void add_command_list(char * command, int line);
void add_extern_symbol(char * externTable,int externAddress);
void free_extern_symbols();
void update_entry_symbol (char* command);
void entry_bubble_sort(struct entrySymbol *start) ;
void entry_swap(struct entrySymbol *a, struct entrySymbol *b) ;
void command_bubble_sort(struct commandList *start) ;
void command_swap(struct commandList *a, struct commandList *b) ;

/*printWord.c*/
void operand_externi (void);
void create_data_word (char* command,char* completeArray,char* zeros);
void create_string_word (char* command,char* completeArray);
void operand_interni (int,char* completeArray,char* firstOpr,char* secondOpr);
void operand_number (int,char* completeArray ,char* firstOpr,char* secondOpr);
void operand_distance (char* command,char* completeArray);
void two_operands_first(char* operand,int srcCodeLine);
void two_operands_second(char* operand,int srcCodeLine);



