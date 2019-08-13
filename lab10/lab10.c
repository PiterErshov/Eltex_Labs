#include "prot.h"



int main(int argc, char *argv[])
{
	int result;
	pthread_t threads[N];
	void *status[atoi(argv[1])];	
	//pthread_cond_t cv[atoi(argv[1])];
	int ret;
	
	char b[N] = "";
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		strcat(b, "1");
		strcpy(put.data[i], b);		
	}

	for (int i = 0; i < atoi(argv[1]); i++)
	{
		result = pthread_create(&threads[i], NULL, fighter, &put.data[i]);		
		if (result != 0)
		{
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < atoi(argv[1]); i++)
		pthread_mutex_unlock(&put.mutex);
//*
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		result = pthread_join(threads[i], &status[i]);
		if (result != 0)
		{
			perror("Joining the first thread");
			return EXIT_FAILURE;
		}
		free(status[i]);
	}
//*/
	return 0;
}
