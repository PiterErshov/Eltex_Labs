#include "prot.h"

int main(int argc, char *argv[])
{

	if (argc < 4)		/* Test for correct number of parameters */
	{
		fprintf(stderr,
			"Usage:  %s <IP Address> <Port> <Send String>\n",
			argv[0]);
		exit(1);
	}

	broadcastIP = argv[1];
	broadcastPort = atoi(argv[2]);
	TCPport = argv[3];
	
	int result;
	pthread_t threads[2];
	void *status[2];
	
	result = pthread_create(&threads[0], NULL, broadcaster, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
		
	result = pthread_create(&threads[1], NULL, TCPcon, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 2; i++)
	{
		result = pthread_join(threads[i], &status[i]);
		if (result != 0)
			return EXIT_FAILURE;
	}
	return 0;
}
