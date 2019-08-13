#include "prot.h"

void *fighter(void *arg)
{
    int i = arg, res, pt;
    void *status;
    pthread_mutex_lock(&put.mutex[i]);
    while(1)
    {
		srand(time(NULL));
		srand(rand());
		pt = 0 + rand() % put.max;
		if(pt != i && live(pt))
			break;
	}
    printf("Thread %d ready\n", i);
    printf("Thread %d kill thread %d\n", i, pt);
    res = pthread_join(put.threads[pt], &status);
    if (res != 0)
        return EXIT_FAILURE;
    
    put.w = i;    
    pthread_exit(NULL);
}
