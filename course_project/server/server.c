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
	struct msgbuf test;
	int msqid = 0;
	
	broadcastIP = argv[1];
	broadcastPort = atoi(argv[2]);
	//TCPport = argv[3];
	strcpy(BM.TCPport_one, argv[3]);
	strcpy(BM.TCPport_two, argv[4]);
	struct mess m;
	
	msqid = msgget(0, 0600 |IPC_CREAT|IPC_EXCL);
	
	
	
	//printf("C %d \n", buf.m[0].size);
	
	//for(int i = 0; i < 10; i++)
	//{
		m.size =1 + 10;
		buf.m[1] = m;
		buf.mtype = 1;
		printf("DD %d\n", msgsnd(msqid, &buf, sizeof (buf.m[1]), 0));
	//	buf.mtype = 0;
//	}
	//for(int i = 0; i < 10; i++)
	//{
		msgrcv(msqid, &test, sizeof (struct msgbuf) - sizeof (long), buf.mtype, IPC_NOWAIT);
		printf("C %d\n", test.m[1].size);
//	}
	//printf("BUF.m[0] = %d, BUF.m[1] = %d", buf.m[0].size, buf.m[1].size);
	/*
	int result;
	pthread_t threads[2];
	void *status[2];
	result = pthread_create(&threads[0], NULL, broadcaster, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	//*
	result = pthread_create(&threads[1], NULL, TCPcon, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < 1; i++)
	{
		result = pthread_join(threads[i], &status[i]);
		if (result != 0)
			return EXIT_FAILURE;
	}
	//*/
	return 0;
}
