#include "prot.h"

int main(int argc, char *argv[])
{
	int sock;	/* Socket */	
	struct sockaddr_in broadcastAddr;	/* Broadcast address */
	char *broadcastIP;	/* IP broadcast address */
		/* Server port */
	char *sendString;	/* String to broadcast */
	int broadcastPermission;	/* Socket opt to set permission to broadcast */
	unsigned int sendStringLen;	/* Length of string to broadcast */
	
	flag = 0;
	if (argc < 4)		/* Test for correct number of parameters */
	{
		fprintf(stderr,
			"Usage:  %s <IP Address> <Port> <Send String>\n",
			argv[0]);
		exit(1);
	}

	broadcastIP = argv[1];	/* First arg:  broadcast IP address */
	broadcastPort = atoi(argv[2]);	/* Second arg:  broadcast port */
	sendString = argv[3];	/* Third arg:  string to broadcast */

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

	sendStringLen = strlen(sendString);	/* Find length of sendString */
		
	int result;
	pthread_t threads;
	void *status;

	result = pthread_create(&threads, NULL, broadcaster, NULL);
	if (result != 0)
	{
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}	
	
	for (int i = 0;; i++)		/* Run forever */
	{
		
		if (flag == 1)
			break;
		/* Broadcast sendString in datagram to clients every 3 seconds */
		if (sendto(sock, sendString, sendStringLen, 0,
			   (struct sockaddr *) &broadcastAddr,
			   sizeof (broadcastAddr)) != sendStringLen)
			printf("Error");
		
		sleep(1);	/* Avoids flooding the network */
	}
	
	result = pthread_join(threads, &status);
	if (result != 0)
		return EXIT_FAILURE;
	close(sock);
	return 0;
}
