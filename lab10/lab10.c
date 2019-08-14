#include "prot.h"

int main(int argc, char *argv[])
{
	int result;
	pthread_t threads[N];
	void *status[atoi(argv[1])];
	int ret;
	put.max = atoi(argv[1]);
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		pthread_mutex_init(&put.mutex[i], NULL);
		result = pthread_create(&put.threads[i], NULL, fighter, &i);
		if (result != 0)
		{
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}
		put.kill[i] = 0;
	}
	
	pthread_cond_broadcast(&cond);
	/*
	for (int i = 0; i < put.max; i++)
	{
		if (put.kill[i] != 1)
		{
			result = pthread_join(put.threads[i], &status[i]);
			if (result != 0)
				return EXIT_FAILURE;
		}
	}
	//*/
	//printf("Победитель = %d\n", put.w);

	return 0;
}
