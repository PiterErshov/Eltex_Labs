#--- Makefile
lab10 : lab10.o fun.o
	gcc -pthread lab10.o fun.o -o lab10
lab10.o : lab10.c
	gcc -pthread -g -c lab10.c
fun.o : fun.c
	gcc -pthread -g -c fun.c
clean :
	rm lab10 *.o
#---------------
