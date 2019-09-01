#--- Makefile
server : server.o server_fun.o
	gcc -pthread server.o server_fun.o -o server
server.o : server.c
	gcc -pthread -g -c server.c
server_fun.o : server_fun.c
	gcc -pthread -g -c server_fun.c
clean :
	rm server *.o
#---------------
