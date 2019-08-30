#--- Makefile
client_1 : client_1.o fun.o
	gcc -pthread client_1.o fun.o -o client_1
client_1.o : client_1.c
	gcc -pthread -g -c client_1.c
fun.o : fun.c
	gcc -pthread -g -c fun.c
clean :
	rm client_1 *.o
#---------------
