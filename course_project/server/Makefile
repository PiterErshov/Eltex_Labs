#--- Makefile
server : server.o fun.o
	gcc -pthread server.o fun.o -o server
server.o : server.c
	gcc -pthread -g -c server.c
fun.o : fun.c
	gcc -pthread -g -c fun.c
clean :
	rm server *.o
#---------------
