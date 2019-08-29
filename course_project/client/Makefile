#--- Makefile
client : client.o fun.o
	gcc -pthread client.o fun.o -o client
client.o : client.c
	gcc -pthread -g -c client.c
fun.o : fun.c
	gcc -pthread -g -c fun.c
clean :
	rm client *.o
#---------------
