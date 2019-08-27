#include "prot.h"


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <Broadcast Port> <Broadcast IP>\n", argv[0]);
		exit(1);
	}

	broadcastPort = atoi(argv[1]);
	broadcastIP = argv[2];


	int result;
	pthread_t threads;
	void *status;

	result = pthread_create(&threads, NULL, broadcast_recv, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	result = pthread_join(threads, &status);
	if (result != 0)
		return EXIT_FAILURE;
	return 0;
}
