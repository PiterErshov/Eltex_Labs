#include "client_1_prot.h"

void *broadcast_recv(void *agv)
{
	int sock, result, recvStringLen, TTS = *(int*)agv;
	pthread_t threads;
	void *status;
	struct sockaddr_in broadcastAddr;

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error. broadcast_recv socket");

	memset(&broadcastAddr, 0, sizeof (broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_addr.s_addr = inet_addr(IP);
	broadcastAddr.sin_port = htons(Port);

	if (bind(sock, (struct sockaddr *) &broadcastAddr,
		 sizeof (broadcastAddr)) < 0)
		printf("Error. broadcast_recv bind");

	int p = sizeof (broadcastAddr);
	if ((recvStringLen = recvfrom(sock, TCPport, sizeof(TCPport), 0,
		      (struct sockaddr *) &broadcastAddr, &p)) < 0)
		printf("Error. broadcast_recv recvfrom");
	TCP_IP = inet_ntoa(broadcastAddr.sin_addr);//getting IP server

	printf("Received: %d\n", atoi(TCPport));
	close(sock);
	result = pthread_create(&threads, NULL, TCPcon, &TTS);
	if (result != 0)
		perror("Creating the first thread");

	result = pthread_join(threads, &status);
	if (result != 0)
		printf("Creating the first thread");

	sleep(TTS);
	pthread_exit(NULL);
}

void *TCPcon(void *agv)
{
	int sock;
	int TTS = *(int*)agv;
	struct mess m;
	struct sockaddr_in echoServAddr;
	int size_mas, totalBytesRcvd;

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error. TCPcon socket");

	memset(&echoServAddr, 0, sizeof (echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(TCP_IP);
	echoServAddr.sin_port = htons(atoi(TCPport));

	if (connect(sock, (struct sockaddr *) &echoServAddr,
		    sizeof (echoServAddr)) < 0)
		printf("Error. TCPcon connect");
	m.time = TTS;
	strcpy(m.message, message);
	m.size = strlen(message);
	if (send(sock,	&m, sizeof(m), 0) < 0)
        printf("Error TCPcon send\n");
	close(sock);
	pthread_exit(NULL);
}
