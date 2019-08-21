#include "prot.h"

void *broadcaster(void *agv)
{
	int sock;
	struct sockaddr_in broadcastAddr;	/* Broadcast address */
	char *broadcastIP, *sendString;	/* IP broadcast address */
 	int broadcastPermission;	/* Socket opt to set permission to broadcast */
	unsigned int sendStringLen;	/* Length of string to broadcast */
	char *sendOut;		/* String to broadcast */
	unsigned int sendOutLen;
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error");
	/* Construct bind structure */
	memset(&broadcastAddr, 0, sizeof (broadcastAddr));	/* Zero out structure */
	broadcastAddr.sin_family = AF_INET;	/* Internet address family */
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);	/* Any incoming interface */
	broadcastAddr.sin_port = htons(outPort);	/* Broadcast port */
	//printf("Received 2: %s\n", inet_ntoa(broadcastAddr.sin_addr));
	/* Bind to the broadcast port */
	
	sendOut = "1";
	sendOutLen = strlen(sendOut);
	/* Receive a single datagram from the server */
	if (sendto(sock, sendOut, sendOutLen, 0, (struct sockaddr *) &broadcastAddr,
	     sizeof (broadcastAddr)) != sendOutLen)
		printf("Error");
	close(sock);
	pthread_exit(NULL);
}
