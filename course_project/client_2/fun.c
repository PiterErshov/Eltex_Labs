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
	if ((recvStringLen = recvfrom(sock, TCPport, sizeof(TCPport), 0,
		      (struct sockaddr *) &broadcastAddr, &p)) < 0)
		printf("Error. broadcast_recv recvfrom");
	outIP = inet_ntoa(broadcastAddr.sin_addr);
	printf("Received: %d\n",  atoi(TCPport));
	fflush(stdout);
	close(sock);
//*
	result = pthread_create(&threads, NULL, TCPcon, NULL);
	if (result != 0)
		perror("Creating the first thread");

	result = pthread_join(threads, &status);
	if (result != 0)
		printf("Creating the first thread");
//*/
	sleep(TTS);
	pthread_exit(NULL);
}

void *TCPcon(void *agv)
{
	int sock, result;
	struct sockaddr_in echoServAddr;
	char *servIP;
	char *echoString;
	pthread_t threads;
	void *status;

	unsigned int echoStringLen;
	int size_mas, totalBytesRcvd;

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error. TCPcon socket");

	memset(&echoServAddr, 0, sizeof (echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(outIP);
	echoServAddr.sin_port = htons(atoi(TCPport));

	if (connect(sock, (struct sockaddr *) &echoServAddr,
		    sizeof (echoServAddr)) < 0)
		printf("Error. TCPcon connect");
		
	if ((recv(sock, &m, sizeof(m), 0)) <= 0)
		printf("Error. TCPcon recv");
	TTS = m.time;

	printf("MMM %s\n", m.message);
	fflush(stdout);
	close(sock);
	pthread_exit(NULL);
}
