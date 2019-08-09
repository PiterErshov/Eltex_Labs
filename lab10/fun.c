#include "prot.h"

void *fighter(void *arg)
{
	char str[N];
	strcpy(str, arg);
	printf("STR = %s\n", arg);
	pthread_exit(NULL);
}
