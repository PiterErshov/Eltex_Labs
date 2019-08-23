#include "prot.h"

void *broadcaster(void *agv)
{
	int sock;
	struct sockaddr_in broadcastAddr;


	int broadcastPermission;
	unsigned int sendStringLen;

	flag = 0;
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error");

	broadcastPermission = 1;
	if (setsockopt
	    (sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
	     sizeof (broadcastPermission)) < 0)
		printf("Error");

	memset(&broadcastAddr, 0, sizeof (broadcastAddr));
	broadcastAddr.sin_family = AF_INET;	
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);	
	broadcastAddr.sin_port = htons(broadcastPort);

	sendStringLen = strlen(TCPport);
	
	for (;;)
	{
		if (flag == 1)
			break;
		if (sendto(sock, TCPport, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof (broadcastAddr)) != sendStringLen)
			printf("Error");

		sleep(1);
	}
	close(sock);
	pthread_exit(NULL);
}

void *broadcast_s(void *agv)
{
	int sock;
	struct sockaddr_in broadcastAddr;
	int recvStringLen;
	char recvString[MAXRECVSTRING + 1];
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error");
	memset(&broadcastAddr, 0, sizeof (broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_port = htons(atoi("1111"));
	printf("Received func: %s\n", inet_ntoa(broadcastAddr.sin_addr));

	if (bind(sock, (struct sockaddr *) &broadcastAddr,
		 sizeof (broadcastAddr)) < 0)
		printf("Error");
	int fl = 0;
	while (1)
	{
		int p = sizeof (broadcastAddr);
		if ((recvStringLen =
		     recvfrom(sock, recvString, MAXRECVSTRING, 0,
			      (struct sockaddr *) &broadcastAddr, &p)) < 0)
			printf("Error\n");
		else
		{
			fl++;
			printf("Received recv: %s\n", inet_ntoa(broadcastAddr.sin_addr));
		}
		if (fl > 1)
			break;
		fl++;
	}
	if (1 == atoi(recvString) || fl != 0)
	{
		flag = 1;
		close(sock);
		pthread_exit(NULL);
	}
}

void *TCPcon(void *agv)
{
	int servSock;
	int clntSock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned int clntLen;
	char *b; 

	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error\n");

	memset(&echoServAddr, 0, sizeof (broadcastIP));	
	echoServAddr.sin_family = AF_INET;	
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	echoServAddr.sin_port = htons(atoi(TCPport));

	if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof (echoServAddr)) < 0)
		printf("Error\n");
	if (listen(servSock, MAXPENDING) < 0)
		printf("Error\n");
	
	b = malloc(sizeof(int)*RCVBUFSIZE);
	
	strcpy(b, "34");
	int x = 2, y = 3;
	for (;;)
	{
		clntLen = sizeof (echoClntAddr);
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
			printf("Error\n");
		printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

		if (send(clntSock, &x, sizeof(int), 0) < 0)
            printf("Error\n");
        if (send(clntSock, &y, sizeof(int), 0) < 0)
            printf("Error\n");
        if (send(clntSock,	b, sizeof(b), 0) < 0)
            printf("Error\n");          
	}
	pthread_exit(NULL);
}
