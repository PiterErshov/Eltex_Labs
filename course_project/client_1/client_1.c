#include "prot.h"


int main(int argc, char *argv[])
{
	int result, TTS = 0;
	pthread_t threads;
	void *status;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s <Broadcast Port> <Broadcast IP>\n", argv[0]);
		exit(1);
	}

	broadcastPort = atoi(argv[1]);
	broadcastIP = argv[2];
	TTS = atoi(argv[3]);
	request = argv[4];
	for(;;)
	{
		result = pthread_create(&threads, NULL, broadcast_recv, &TTS);
		if (result != 0)
		{
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}

		result = pthread_join(threads, &status);
		if (result != 0)
			return EXIT_FAILURE;
	}
	return 0;
}
