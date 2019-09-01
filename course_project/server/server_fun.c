#include "server_prot.h"

void *broadcast_type1(void *agv)
{
	int sock;
	struct sockaddr_in broadcastAddr[BROADPORTS];
	int broadcastPermission;
	unsigned int sendStringLen;

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error broadcaster socket\n");

	broadcastPermission = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
	     sizeof (broadcastPermission)) < 0)
		printf("Error broadcaster setsockopt\n");
	for(int i = 0; i < BROADPORTS; i++)
	{
		memset(&broadcastAddr[i], 0, sizeof (broadcastAddr[i]));
		broadcastAddr[i].sin_family = AF_INET;	
		broadcastAddr[i].sin_addr.s_addr = inet_addr(broadcastIP);	
		broadcastAddr[i].sin_port = htons(bPort1 + i);
	}

	for (;;)
	{	
		for(int i = 0; i < BROADPORTS; i++)
		{
			if(size_of < N)		
			{	
				if (sendto(sock, TCPport_one, strlen(TCPport_one), 0, (struct sockaddr *) &broadcastAddr[i], 
					sizeof (broadcastAddr[i])) < 0)
					printf("Error broadcaster sendto1\n");
			}						
		}
	}
	close(sock);
	pthread_exit(NULL);
}

void *broadcast_type2(void *agv)
{	
	int sock;
	struct sockaddr_in broadcastAddr[BROADPORTS];
	int broadcastPermission;
	unsigned int sendStringLen;

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error broadcaster socket\n");

	broadcastPermission = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
	     sizeof (broadcastPermission)) < 0)
		printf("Error broadcaster setsockopt\n");
	for(int i = 0; i < BROADPORTS; i++)
	{
		memset(&broadcastAddr[i], 0, sizeof (broadcastAddr[i]));
		broadcastAddr[i].sin_family = AF_INET;	
		broadcastAddr[i].sin_addr.s_addr = inet_addr(broadcastIP);	
		broadcastAddr[i].sin_port = htons(bPort2 + i);
	}

	for (;;)
	{	
		for(int i = 0; i < BROADPORTS; i++)
		{
			if(size_of != 0)		
			{
				if (sendto(sock, TCPport_two, strlen(TCPport_two), 0, (struct sockaddr *) &broadcastAddr[i],
					sizeof (broadcastAddr[i])) < 0)
					printf("Error broadcaster sendto2\n");
			}
			sleep(1);
		}
	}
	close(sock);
	pthread_exit(NULL);
}

void *TCPconOne(void *agv)
{
	fflush(stdout);
	int servSock;
	int clntSock;
	int result;
	pthread_t threads;
	void *status;
	int msqid = *(int*)agv;	
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned int clntLen;

	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error TCPconOne socket\n");

	memset(&echoServAddr, 0, sizeof (broadcastIP));	
	echoServAddr.sin_family = AF_INET;	
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	echoServAddr.sin_port = htons(atoi(TCPport_one));
 
	if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof (echoServAddr)) < 0)
		printf("Error TCPconOne bind\n");
	if (listen(servSock, BROADPORTS) < 0)
		printf("Error TCPconOne listen\n");
			
	for (;;)
	{	
		clntLen = sizeof (echoClntAddr);
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
			printf("Error TCPconOne accept\n");
		else
			printf("first type client connected\n");
		result = pthread_create(&threads, NULL, TCPrecvOne, &clntSock);
		if (result != 0)
			perror("Creating the first thread");
			
		result = pthread_join(threads, &status);
		if (result != 0)
			perror("Join the first thread");

		pthread_mutex_lock(&mutex);   		
		
		mtype = 1;
		msgsnd(msqid, &buf, sizeof(buf.message), 0);
		pthread_mutex_unlock(&mutex); 
		
	}
	pthread_exit(NULL);
}

void *TCPrecvOne(void *agv)
{
	int clntSock = *(int*)agv;
	if ((recv(clntSock, &buf, sizeof(buf), 0)) <= 0)
			printf("Error TCPconOne recv\n");
	else 
		size_of+= 1;
	pthread_exit(NULL);
}


void *TCPconTwo(void *agv)
{
	int servSock;
	int clntSock;
	int msqid = *(int*)agv;
	int result;
	pthread_t threads;
	void *status;
	struct msgbuf out;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned int clntLen;

	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error TCPconTwo socket\n");

	memset(&echoServAddr, 0, sizeof (broadcastIP));	
	echoServAddr.sin_family = AF_INET;	
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	echoServAddr.sin_port = htons(atoi(TCPport_two));

	if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof (echoServAddr)) < 0)
		printf("Error TCPconTwo bind\n");
	if (listen(servSock, BROADPORTS) < 0)
		printf("Error TCPconTwo listen\n");

	for (;;)
	{ 
		if(size_of != 0)		
		{
			clntLen = sizeof (echoClntAddr);
			if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
				printf("Error TCPconTwo accept\n");
			else
				printf("second type client connected\n");
			msgrcv(msqid, &out, sizeof (struct msgbuf) - sizeof (long), mtype, IPC_NOWAIT);
			result = pthread_create(&threads, NULL, TCPsendTwo, &clntSock);
			if (result != 0)
				perror("Creating the first thread");
				
			result = pthread_join(threads, &status);
			if (result != 0)
				perror("Join the first thread");
		}
	}
	pthread_exit(NULL);
}

void *TCPsendTwo(void *agv)	
{
	pthread_mutex_lock(&mutex); 
	int clntSock = *(int*)agv;
	if (send(clntSock,	&buf, sizeof(buf), 0) < 0)
		printf("Error TCPconTwo send\n");
	else 
		size_of -= 1;
	pthread_mutex_unlock(&mutex); 
	pthread_exit(NULL);
}
