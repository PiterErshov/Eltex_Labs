#include "prot.h"

void *broadcaster(void *agv)
{
	int sock;		/* Socket */
	struct sockaddr_in broadcastAddr;	/* Broadcast address */


	int broadcastPermission;	/* Socket opt to set permission to broadcast */
	unsigned int sendStringLen;	/* Length of string to broadcast */

	flag = 0;

	/* Create socket for sending/receiving datagrams */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error");

	/* Set socket to allow broadcast */
	broadcastPermission = 1;
	if (setsockopt
	    (sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
	     sizeof (broadcastPermission)) < 0)
		printf("Error");

	/* Construct local address structure */
	memset(&broadcastAddr, 0, sizeof (broadcastAddr));	/* Zero out structure */
	broadcastAddr.sin_family = AF_INET;	/* Internet address family */
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);	/* Broadcast IP address */
	broadcastAddr.sin_port = htons(broadcastPort);	/* Broadcast port */

	sendStringLen = strlen(TCPport);	/* Find length of sendString */

	for (int i = 0;; i++)	/* Run forever */
	{
		if (flag == 1)
			break;
		/* Broadcast sendString in datagram to clients every 3 seconds */
		if (sendto(sock, TCPport, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof (broadcastAddr)) != sendStringLen)
			printf("Error");

		sleep(1);	/* Avoids flooding the network */
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
	char *Buffer; 

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
	
	Buffer = malloc(sizeof(int)*RCVBUFSIZE);
	//strcmp(Buffer, "HELLO");
	//Buffer[RCVBUFSIZE] = '\0';
	for (;;)
	{
		clntLen = sizeof (echoClntAddr);
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
			printf("Error\n");
		printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

		if (send(clntSock, , RCVBUFSIZE, 0) < 0)
            printf("Error\n");
      // if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        //    printf("Error\n");
		//HandleTCPClient(clntSock);
	}
	pthread_exit(NULL);
}
