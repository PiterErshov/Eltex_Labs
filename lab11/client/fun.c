#include "prot.h"

void *broadcast_recv(void *agv)
{
	//pthread_mutex_lock(&mutex);
	int sock;
	struct sockaddr_in broadcastAddr;
	char recvString[MAXRECVSTRING + 1];
	int recvStringLen;
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error. broadcast_recv socket");

	memset(&broadcastAddr, 0, sizeof (broadcastAddr));	/* Zero out structure */
	broadcastAddr.sin_family = AF_INET;	/* Internet address family */
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);	/* Any incoming interface */
	broadcastAddr.sin_port = htons(broadcastPort);	/* Broadcast port */

	/* Bind to the broadcast port */
	if (bind(sock, (struct sockaddr *) &broadcastAddr,
		 sizeof (broadcastAddr)) < 0)
		printf("Error. broadcast_recv bind");

	/* Receive a single datagram from the server */
	int p = sizeof (broadcastAddr);
	if ((recvStringLen =
	     recvfrom(sock, recvString, MAXRECVSTRING, 0,
		      (struct sockaddr *) &broadcastAddr, &p)) < 0)
		printf("Error. broadcast_recv recvfrom");
	outIP = inet_ntoa(broadcastAddr.sin_addr);
	recvString[recvStringLen] = '\0';

	outPort = atoi(recvString);
	printf("Received: %d\n", outPort);	/* Print the received string */

	close(sock);
//	pthread_mutex_unlock(&mutex);

	int result;
	pthread_t threads;
	void *status;
	result = pthread_create(&threads, NULL, TCPcon, NULL);
	if (result != 0)
		perror("Creating the first thread");
	
	result = pthread_join(threads, &status);
	if (result != 0)
		printf("Creating the first thread");
		//return EXIT_FAILURE;
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
//*
void *TCPcon(void *agv)
{
	int sock;
	struct sockaddr_in echoServAddr;
	char *servIP;
	char *echoString;
	char echoBuffer[RCVBUFSIZE];
	unsigned int echoStringLen;
	int bytesRcvd, totalBytesRcvd;

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error. TCPcon socket");
	//pthread_mutex_lock(&mutex);
	memset(&echoServAddr, 0, sizeof (echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(outIP);
	echoServAddr.sin_port = htons(outPort);

	if (connect
	    (sock, (struct sockaddr *) &echoServAddr,
	     sizeof (echoServAddr)) < 0)
		printf("Error. TCPcon connect");
	echoString = "Die";
	echoStringLen = strlen(echoString);

	//if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
	//      printf("Error");

	totalBytesRcvd = 0;
//      printf("Received: ");   
	//while (totalBytesRcvd < echoStringLen)
	//{
	if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE, 0)) <= 0)
		printf("Error. TCPcon recv");
	//      totalBytesRcvd += bytesRcvd;
	echoBuffer[bytesRcvd] = '\0';
	printf("TTTT %s", echoBuffer);
	//      if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
	//      printf("Error");
	//}

	printf("\n");
	//pthread_mutex_unlock(&mutex);
	close(sock);
	pthread_exit(NULL);
}
