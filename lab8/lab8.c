#include <stdio.h>
#include <stdlib.h>
#include "prot.h"

int main(int argc, char *argv[])
{
	FILE *a[argc - 1];
	struct msgbuf test;
	char **ch;	
	int msqid = 0, b = 0;
	int sum[argc - 1];
		
	msqid = msgget(0, 0600 |IPC_CREAT|IPC_EXCL);
	
	ch = (char **) malloc(sizeof (char *) * (argc - 1));

	for (int i = 1; i < argc; i++)
	{
		if ((a[i] = fopen(argv[i], "r")) == NULL)
		{
			printf("Невозможно открыть файл для чтения.\n");
			exit(1);
		}
		else
			printf("file's name: %s\n", argv[i]);
	}

	process_file(a, ch, msqid, argc);
	
	for (int i = 0; i < argc - 1; i++)
	{
		msgrcv(msqid, &test, sizeof (struct msgbuf) - sizeof (long), buf.mtype, IPC_NOWAIT);
		printf("Controll summ in file %s = %d \n", argv[i + 1], test.mSum[i]);
	}

	free(ch);

	for (int i = 1; i < argc - 1; i++)
		fclose(a[i]);

	return 0;
}
