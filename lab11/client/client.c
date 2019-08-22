#include "prot.h"


int main(int argc, char *argv[])
{
	if (argc != 3)		/* Test for correct number of arguments */
	{
		fprintf(stderr, "Usage: %s <Broadcast Port>\n", argv[0]);
		exit(1);
	}

	broadcastPort = atoi(argv[1]);	/* First arg: broadcast port */
	broadcastIP = argv[2];

	
	int result;
	pthread_t threads[2];
	void *status[2];

	result = pthread_create(&threads[0], NULL, broadcast_recv, NULL);
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
