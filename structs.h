
static struct cmds{
 char *name;
 void (*func)(char * ,char *,int );
 } cmd[]={
 {"mov",mov},
 {"cmp",cmp},
 {"add",add},
 {"sub",sub},
 {"lea",lea},
 {"clr",clr},
 {"not",not},
 {"inc",inc},
 {"dec",dec},
 {"jmp",jmp},
 {"bne",bne},
 {"jsr",jsr},
 {"red",red},
 {"prn",prn},
 {"rts",rts},
 {"stop",stop},
 {"NULL",NULL},
 };


