#--- Makefile
client_1 : client_1.o client_1_fun.o
	gcc -pthread client_1.o client_1_fun.o -o client_1
client_1.o : client_1.c
	gcc -pthread -g -c client_1.c
client_1_fun.o : client_1_fun.c
	gcc -pthread -g -c client_1_fun.c
clean :
	rm client_1 *.o
#---------------
