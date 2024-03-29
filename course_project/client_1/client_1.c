#include "client_1_prot.h"

int main(int argc, char *argv[])
{
	int result, TTS = 0;
	pthread_t threads;
	void *status;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s <Broadcast Port> <Broadcast IP> <Tame to sleep>\n", argv[0]);
		exit(1);
	}

	Port = atoi(argv[1]);
	IP = argv[2];
	TTS = atoi(argv[3]);
	message = argv[4];
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
