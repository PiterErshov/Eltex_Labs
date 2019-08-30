#--- Makefile
client_2 : client_2.o fun.o
	gcc -pthread client_2.o fun.o -o client_2
client_2.o : client_2.c
	gcc -pthread -g -c client_2.c
fun.o : fun.c
	gcc -pthread -g -c fun.c
clean :
	rm client_2 *.o
#---------------
