#include <stdio.h>
#include <stdlib.h>
#include "prot.h"

int main(int argc, char *argv[])
{
	struct msgbuf test;	
	char **ch;	
	int msqid = 0, b = 0;
				
	msqid = msgget(0, 0600 |IPC_CREAT|IPC_EXCL);	
	ch = malloc(sizeof (char *) * (argc - 1));

	process_file(ch, msqid, argc, argv);
	
	for (int i = 0; i < argc - 1; i++)
	{
		msgrcv(msqid, &test, sizeof (struct msgbuf) - sizeof (long), buf.mtype, IPC_NOWAIT);
		printf("Controll summ in file %s = %d \n", argv[i + 1], test.mSum[i]);
	}
	free(ch);
	return 0;
}
