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
		printf("Error2\n");
	if (listen(servSock, MAXPENDING) < 0)
		printf("Error\n");
	
	
	b = malloc(sizeof(int)* (x * y));
	b = map_creat(x, y);

	   
	for (;;)
	{
		clntLen = sizeof (echoClntAddr);
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
			printf("Error1\n");
		printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

		if (send(clntSock, &x, sizeof(int), 0) < 0)
            printf("Error2\n");
        if (send(clntSock, &y, sizeof(int), 0) < 0)
            printf("Error3\n");
        if (send(clntSock,	b, x * y, 0) < 0)
            printf("Error4\n");          
	}
	pthread_exit(NULL);
}

char* map_creat(int x, int y)
{
	char **map = calloc(x, sizeof(char * ));
	char *outmap = malloc(sizeof(char) * (x * y));
	for(int i =0; i < x; i++)
	{
		map[i] = calloc(y, sizeof(char));
		for(int j = 0; j < y; j++)
		{
			srand(rand());
			int f = rand() % 2;
			if(f == 0)
				map[i][j] = '0';
			if(f == 1)
				map[i][j] = '1';
		}
	}
	int k = 0;
	for(int i =0; i < x; i++)
		for(int j = 0; j < y; j++)
		{
			outmap[k] = map[i][j];
			if(k < x * y)
				k++;
		}
	return outmap;
}
