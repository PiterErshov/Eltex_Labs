#--- Makefile
lab6 : lab6.o f.o
	gcc -std=c99 lab6.o f.o -o lab6
f.o : f.c
	gcc -std=c99 -g -c f.c
lab6.o : lab6.c
	gcc -std=c99 -g -c lab6.c
clean :
	rm lab6 lab6.o f.o
#---------------
