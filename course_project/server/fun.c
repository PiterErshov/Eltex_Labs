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

	for (;;)
	{
		if (flag == 1)
			break;
		if (sendto(sock, &BM, sizeof(BM), 0, (struct sockaddr *) &broadcastAddr, sizeof (broadcastAddr)) != sendStringLen)
			printf("Error");

		sleep(1);
	}
	close(sock);
	pthread_exit(NULL);
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
	echoServAddr.sin_port = htons(atoi(BM.TCPport_one));

	if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof (echoServAddr)) < 0)
		printf("Error2\n");
	if (listen(servSock, MAXPENDING) < 0)
		printf("Error\n");
	
	
	//b = malloc(sizeof(int)* (x * y));
	//b = map_creat(x, y);
	struct mess m;
	
	m.time = 10;
	strcpy(m.message,"123456789");
	m.size = sizeof(m.message);
	
	for (;;)
	{
		clntLen = sizeof (echoClntAddr);
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
			printf("Error1\n");

        if (send(clntSock,	&m, sizeof(m), 0) < 0)
            printf("Error4\n");
	}
	free(b);
	pthread_exit(NULL);
}

void freeMas(char **mas, int y)	//очистка массива
{
	for (int i = 0; i < y; i++)
		free(mas[i]);
	free(mas);
}
