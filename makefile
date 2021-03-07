myprog: main.o createWord.o operations.o checks.o firstRound.o secondRound.o files.o printWord.o symbolsList.o
	gcc -g -ansi -Wall -pedantic main.o createWord.o operations.o checks.o firstRound.o secondRound.o files.o printWord.o symbolsList.o -o myprog -lm
main.o:	main.c header.h
	gcc -c -ansi -Wall -pedantic  main.c -o main.o	
createWord.o:	createWord.c header.h
	gcc -c -ansi -Wall -pedantic createWord.c -o createWord.o -lm	
operations.o:	operations.c header.h
	gcc -c -ansi -Wall -pedantic operations.c -o operations.o -lm
checks.o:	checks.c header.h
	gcc -c -ansi -Wall -pedantic checks.c -o checks.o -lm
firstRound.o:	firstRound.c header.h structs.h
	gcc -c -ansi -Wall -pedantic firstRound.c -o firstRound.o -lm
secondRound.o:	secondRound.c header.h structs.h
	gcc -c -ansi -Wall -pedantic secondRound.c -o secondRound.o -lm
files.o:	files.c header.h 
	gcc -c -ansi -Wall -pedantic files.c -o files.o -lm
printWord.o:	printWord.c header.h 
	gcc -c -ansi -Wall -pedantic printWord.c -o printWord.o -lm
symbolsList.o:	symbolsList.c header.h 
	gcc -c -ansi -Wall -pedantic symbolsList.c -o symbolsList.o -lm
