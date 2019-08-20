#include "prot.h"


int main(int argc, char *argv[])
{
	int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast Address */
    unsigned short broadcastPort;     /* Port */
    char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
    int recvStringLen;                /* Length of received string */
    char *broadcastIP;
	char *sendOut;	/* String to broadcast */
	unsigned int sendOutLen;
    if (argc != 4)    /* Test for correct number of arguments */
    {
        fprintf(stderr,"Usage: %s <Broadcast Port>\n", argv[0]);
        exit(1);
    }

    broadcastPort = atoi(argv[1]);   /* First arg: broadcast port */
	sendOut = argv[2];
	broadcastIP = argv[3];
    /* Create a best-effort datagram socket using UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
       printf("Error");

    /* Construct bind structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);  /* Any incoming interface */
    broadcastAddr.sin_port = htons(broadcastPort);      /* Broadcast port */

    /* Bind to the broadcast port */
    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
        printf("Error");

    /* Receive a single datagram from the server */
    if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
        printf("Error");

    recvString[recvStringLen] = '\0';
    printf("Received: %s\n", recvString);    /* Print the received string */
    sendOutLen = strlen(sendOut);	
    if (sendto(sock, sendOut, sendOutLen, 0,(struct sockaddr *) &broadcastAddr,
		sizeof (broadcastAddr)) != sendOutLen)
			printf("Error");
    close(sock);
	return 0;
}
