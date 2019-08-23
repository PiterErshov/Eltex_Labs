#include "prot.h"

void *broadcast_recv(void *agv)
{
	int sock, result, recvStringLen;
	pthread_t threads;
	void *status;
	struct sockaddr_in broadcastAddr;
	char recvString[MAXRECVSTRING + 1];
	
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error. broadcast_recv socket");

	memset(&broadcastAddr, 0, sizeof (broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
	broadcastAddr.sin_port = htons(broadcastPort);

	if (bind(sock, (struct sockaddr *) &broadcastAddr,
		 sizeof (broadcastAddr)) < 0)
		printf("Error. broadcast_recv bind");

	int p = sizeof (broadcastAddr);
	if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, (struct sockaddr *) &broadcastAddr, &p)) < 0)
		printf("Error. broadcast_recv recvfrom");
	outIP = inet_ntoa(broadcastAddr.sin_addr);
	recvString[recvStringLen] = '\0';

	outPort = atoi(recvString);
	
	printf("Received: %d\n", recvStringLen);

	close(sock);

	result = pthread_create(&threads, NULL, TCPcon, NULL);
	if (result != 0)
		perror("Creating the first thread");

	result = pthread_join(threads, &status);
	if (result != 0)
		printf("Creating the first thread");

	pthread_exit(NULL);
}

//*
void *TCPcon(void *agv)
{
	int sock, x, y;
	struct sockaddr_in echoServAddr;
	char *servIP;
	char *echoString;
	
	unsigned int echoStringLen;
	int size_mas, totalBytesRcvd;

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error. TCPcon socket");
		
	memset(&echoServAddr, 0, sizeof (echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(outIP);
	echoServAddr.sin_port = htons(outPort);

	if (connect(sock, (struct sockaddr *) &echoServAddr,
	     sizeof (echoServAddr)) < 0)
		printf("Error. TCPcon connect");
	
	if ((size_mas = recv(sock, &x, sizeof(x), 0)) <= 0)
		printf("Error. TCPcon recv");
	//printf("T1 %d\n", x);
	if ((size_mas = recv(sock, &y, sizeof(y), 0)) <= 0)
		printf("Error. TCPcon recv");
	//printf("T1 %d\n", y);
	char *echoBuffer = malloc(sizeof(char) * (x * y));
	if ((recv(sock,	echoBuffer, x * y, 0)) <= 0)
		printf("Error. TCPcon recv");
	printf("T1 %s\n", echoBuffer);
	
	printf("\n");
	close(sock);
	pthread_exit(NULL);
}

void *broadcast_send(void *agv)
{
	pthread_mutex_lock(&mutex);
	int sock;
	struct sockaddr_in broadcastAddr;	/* Broadcast address */
	char *broadcastIP, *sendString;	/* IP broadcast address */
	unsigned int sendOutLen;
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error. broadcast_send socket");
	/* Construct bind structure */
	memset(&broadcastAddr, 0, sizeof (broadcastAddr));	/* Zero out structure */
	broadcastAddr.sin_family = AF_INET;	/* Internet address family */
	broadcastAddr.sin_addr.s_addr = inet_addr(outIP);	/* Any incoming interface */
	broadcastAddr.sin_port = htons(outPort);	/* Broadcast port */

	sendOut = "1";
	sendOutLen = strlen(sendOut);

	/* Receive a single datagram from the server */
	if (sendto
	    (sock, sendOut, sendOutLen, 0, (struct sockaddr *) &broadcastAddr,
	     sizeof (broadcastAddr)) != sendOutLen)
		printf("Error. broadcast_send sendto");
	//pthread_mutex_unlock(&mutex);
	close(sock);
	pthread_exit(NULL);
}
