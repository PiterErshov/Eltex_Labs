#include "prot.h"

int main(int argc, char *argv[])
{
	int result;
	pthread_t threads[N];
	void *status[argc];
	
	file_name = argv;
	for (int i = 0; i < argc - 1; i++)
	{		
		int *f = malloc(sizeof (int));
		*f = i + 1;
		result = pthread_create(&threads[i], NULL, M_x, f);
		if (result != 0)
		{
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}
	}
	for (int i = 0; i < argc; i++)
	{
		result = pthread_join(threads[i], &status[i]);
		if (result != 0)
			return EXIT_FAILURE;
	}

	return 0;
}
