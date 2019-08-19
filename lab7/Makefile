#--- Makefile
lab7 : lab7.o func.o
	gcc -std=c99 lab7.o func.o -o lab7
func.o : func.c
	gcc -std=c99 -g -c func.c
lab7.o : lab7.c
	gcc -std=c99 -g -c lab7.c
clean :
	rm lab7 lab7.o func.o
#---------------
