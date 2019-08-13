#include "prot.h"

void *fighter(void *arg)
{
	pthread_mutex_lock(&put.mutex);
	char str[N];
	strcpy(str, arg);
	printf("STR = %s\n", str);
	pthread_exit(NULL);
}
