#include "prot.h"

int main(int argc, char *argv[])
{	

	int result;
	pthread_t threads[4];
	void *status[4];
	if (argc < 6)		/* Test for correct number of parameters */
	{
		fprintf(stderr,
			"Usage:  %s <IP Address> <Port> <TCP Port> <X> <Y>\n",
			argv[0]);
		exit(1);
	}
	
	int msqid = 0;
	
	broadcastIP = argv[1];
	bPort1 = atoi(argv[2]);
	bPort2 = atoi(argv[3]);
	TCPport_one = argv[4];
	TCPport_two = argv[5];

	/*
	struct mess m;	
	struct msgbuf out;
	int y = 0;

	
	/*
	for(int i = 0; i < 10; i++)
	{
		m.size = i * 10;
		buf.size = m.size;
		buf.mtype = 1;
		msgsnd(msqid, &buf, sizeof(buf.message), 0);
	}
	for(int i = 0; i < 10; i++)
	{
		msgrcv(msqid, &out, sizeof (struct msgbuf) - sizeof (long), buf.mtype, IPC_NOWAIT);
		printf("C %d\n", out.size);
	}
	//*/
	//printf("BUF.m[0] = %d, BUF.m[1] = %d", buf.m[0].size, buf.m[1].size);
	//*
	msqid = msgget(0, 0600 |IPC_CREAT|IPC_EXCL);
	size_of = 0;
	result = pthread_create(&threads[0], NULL, broadcast_type1, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	//*
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
	for (int i = 0; i < 3; i++)
	{
		result = pthread_join(threads[i], &status[i]);
		if (result != 0)
			return EXIT_FAILURE;
	}
	//*/
	return 0;
}
