#include "prot.h"

void *broadcaster(void *agv)
{
	int sock;
	struct sockaddr_in broadcastAddr;
	int recvStringLen;
	char recvString[MAXRECVSTRING + 1];
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("Error");
	memset(&broadcastAddr, 0, sizeof (broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	//broadcastAddr.sin_addr.s_addr = inet_addr("172.21.0.49");
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
		     recvfrom(sock, recvString, MAXRECVSTRING, 0, (struct sockaddr *) &broadcastAddr, &p)) < 0)
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
