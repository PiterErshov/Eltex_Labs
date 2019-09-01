#--- Makefile
client_2 : client_2.o client_2_fun.o
	gcc -pthread client_2.o client_2_fun.o -o client_2
client_2.o : client_2.c
	gcc -pthread -g -c client_2.c
client_2_fun.o : client_2_fun.c
	gcc -pthread -g -c client_2_fun.c
clean :
	rm client_2 *.o
#---------------
