#include "prot.h"

int main(int argc, char *argv[])
{
	int sock, s1;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char *broadcastIP;                /* IP broadcast address */
    unsigned short broadcastPort;     /* Server port */
    char *sendString;                 /* String to broadcast */
	char recvString[255 + 1];
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */

    if (argc < 4)                     /* Test for correct number of parameters */
    {
        fprintf(stderr,"Usage:  %s <IP Address> <Port> <Send String>\n", argv[0]);
        exit(1);
    }

    broadcastIP = argv[1];            /* First arg:  broadcast IP address */ 
    broadcastPort = atoi(argv[2]);    /* Second arg:  broadcast port */
    sendString = argv[3];             /* Third arg:  string to broadcast */

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        printf("Error");
        
    if ((s1 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        printf("Error");
        //DieWithError("socket() failed");

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
          sizeof(broadcastPermission)) < 0)
          printf("Error");
        //DieWithError("setsockopt() failed");

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
    broadcastAddr.sin_port = htons(broadcastPort);         /* Broadcast port */

    sendStringLen = strlen(sendString);  /* Find length of sendString */
	
    for (;;) /* Run forever */
    {	
         /* Broadcast sendString in datagram to clients every 3 seconds*/
         if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) 
               &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
               printf("Error");
             //DieWithError("sendto() sent a different number of bytes than expected");
        
		if (recvfrom(sock, recvString, 255, 0, NULL, 0) > 0)
			if(atoi(recvString) == 1)
				break;
        sleep(1);   /* Avoids flooding the network */
    }
    close(sock);
	return 0;
}
