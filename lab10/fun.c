#include "prot.h"

void *fighter(void *arg)
{
	int i = *(int*)arg, res, pt = 0;
	void *status;
	/*pthread_mutex_lock(&put.mutex[i]);
	/*if (i == put.max - 1)
		for (int j = 0; j < put.max; j++)
			pthread_mutex_unlock(&put.mutex[j]);
	//*/
	//*
	while (1)
	{
		srand(i * time(NULL));
		srand(rand());
		pt = rand() % put.max;
		if (pt != i && live(pt))
			break;
	}
	printf("Thread %d ready\n", i);
	printf("Thread %d kill thread %d\n", i, pt);
	res = pthread_join(put.threads[pt], &status);
	if (res != 0)
		return EXIT_FAILURE;
			

	put.kill[pt] = 1;
	int j = 0;
	while(j < put.max)
	{	
		printf("THREAD %d :KILLED[%d] = %d\n", i, j, put.kill[j]);
		fflush (stdout);
		j++;
	}
	put.w = i;
	pthread_exit(NULL);
}

int live(int pt)
{
	int f = 1;

	if (put.kill[pt] == 0)
		return 1;
	else
		return 0;
}
