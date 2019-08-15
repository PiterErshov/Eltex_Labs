#include "prot.h"

void *fighter(void *arg)
{
	int i = *(int *) arg, res, pt = 0;
	void *status;
	pthread_mutex_t mut;
	
	printf("Thread %d ready\n", i);
	
	fflush(stdout);
	pthread_mutex_lock(&put.mutex[i]);
	flag--;
	while (flag > 0)
	{
		pthread_cond_wait(&cond, &put.mutex[i]);
	}
	pthread_mutex_unlock(&put.mutex[i]);
	printf("Thread %d do\n", i);
	fflush(stdout);
	/*     
	pthread_mutex_lock(&mut);
	if (put.live > 1)
	{
		while (1)
		{
			srand(i * time(NULL));
			srand(rand());
			pt = rand() % put.max;
			if (pt != i && put.kill[pt] == 0)
				break;
			else if (put.live > 1)
				break;
			printf("Pthrear %d\n", pt);
		}		
		if (pt != i && put.kill[pt] == 0)
			printf("Thread %d kill thread %d\n", i, pt);
		pthread_cancel(put.threads[pt]);
		put.kill[pt] = 1;
		put.live--;
		put.w = i;	
	}
	pthread_mutex_unlock(&mut);
	/*
	   int j = 0;
	   while(j < put.max)
	   {    
	   printf("THREAD %d :KILLED[%d] = %d\n", i, j, put.kill[j]);
	   fflush (stdout);
	   j++;
	   }
	   // */
	//pthread_mutex_lock(&put.mutex[i]);
	pthread_exit(NULL);
}
