#include "server_prot.h"

int main(int argc, char *argv[])
{	
	int result;
	pthread_t threads[4];
	void *status[4];

	if (argc < 6)
	{
		fprintf(stderr,
			"Usage:  %s <IP Address> <Broadcast Port 1> <Broadcast Port 2> <TCP Port 1> <TCP Port 2>\n",
			argv[0]);
		exit(1);
	}
	
	int msqid = 0;	
	broadcastIP = argv[1];
	bPort1 = atoi(argv[2]);
	bPort2 = atoi(argv[3]);
	TCPport_one = argv[4];
	TCPport_two = argv[5];

	msqid = msgget(0, 0600 |IPC_CREAT|IPC_EXCL);//creating a message queue
	size_of = 0;
	result = pthread_create(&threads[0], NULL, broadcast_type1, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	result = pthread_create(&threads[1], NULL, broadcast_type2, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	result = pthread_create(&threads[2], NULL, TCPconOne, &msqid);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	result = pthread_create(&threads[3], NULL, TCPconTwo, &msqid);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < 4; i++)
	{
		result = pthread_join(threads[i], &status[i]);
		if (result != 0)
			return EXIT_FAILURE;
	}
	return 0;
}
