#include "prot.h"

void *broadcaster(void *agv)
{
	int sock;
	struct sockaddr_in broadcastAddr;
	char *broadcastIP;
	unsigned short broadcastPort;
	int broadcastPermission;
	int recvStringLen;
	char recvString[MAXRECVSTRING + 1];
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error");
	memset(&broadcastAddr, 0, sizeof (broadcastAddr));
	broadcastAddr.sin_family = AF_INET;	
	broadcastAddr.sin_addr.s_addr = inet_addr("172.21.0.49");
	broadcastAddr.sin_port = htons(atoi("1111"));	

	if (bind(sock, (struct sockaddr *) &broadcastAddr,
		 sizeof (broadcastAddr)) < 0)
		printf("Error");
	int fl = 0;
	while(1)
	{	
		if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
			printf("Error");
		else
			fl++;
		if(fl > 1)
			break;
	}
	if (1 == atoi(recvString) && fl == 2)
	{
		flag = 1;
		close(sock);
		pthread_exit(NULL);
	}
}
