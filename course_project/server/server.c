#include "prot.h"

int main(int argc, char *argv[])
{

	if (argc < 6)		/* Test for correct number of parameters */
	{
		fprintf(stderr,
			"Usage:  %s <IP Address> <Port> <TCP Port> <X> <Y>\n",
			argv[0]);
		exit(1);
	}
	
	int msqid = 0;
	
	broadcastIP = argv[1];
	broadcastPort = atoi(argv[2]);
	//TCPport = argv[3];
	strcpy(BM.TCPport_one, argv[3]);
	strcpy(BM.TCPport_two, argv[4]);

	/*
	struct mess m;	
	
	int y = 0;
	/*
	for(int i = 0; i < 10; i++)
	{
		y += sizeof (buf.m[i]);
		m.size = i * 10;
		buf.m[i] = m;
		buf.mtype = 1;
		msgsnd(msqid, &buf, y, 0);
	}
	for(int i = 0; i < 10; i++)
	{
		msgrcv(msqid, &test, sizeof (struct msgbuf) - sizeof (long), buf.mtype, IPC_NOWAIT);
		printf("C %d\n", test.m[i].size);
	}
	//*/
	//printf("BUF.m[0] = %d, BUF.m[1] = %d", buf.m[0].size, buf.m[1].size);
	//*
	msqid = msgget(0, 0600 |IPC_CREAT|IPC_EXCL);
	int result;
	pthread_t threads[3];
	void *status[3];
	result = pthread_create(&threads[0], NULL, broadcaster, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	//*
	result = pthread_create(&threads[1], NULL, TCPconOne, msqid);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	result = pthread_create(&threads[2], NULL, TCPconTwo, msqid);
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
