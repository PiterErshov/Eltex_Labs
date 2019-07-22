#include <stdio.h>
#include <stdlib.h>
#include "prot.h"
#define MSGKEY 32769
struct msgbuf
{
	long mtype;		/* тип сообщения, должен быть > О */
	int mSum[N];		/* данные */
} buf;

int main(int argc, char *argv[])
{

	FILE *a[argc - 1];
	struct msgbuf buf, test;
	char **ch;
	pid_t pid;
	int s = 0, msqid = 0, b = 0;
	int sum[argc - 1];

	msqid = msgget(MSGKEY, 0600 |IPC_CREAT|IPC_EXCL);

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

	for (int i = 0; i < argc - 1; i++)
	{
		pid = fork();

		if (-1 == pid)
		{
			perror("fork");
			exit(1);
		}
		else if (0 == pid)
		{
			msqid = msgget(0, 0600 |IPC_CREAT|IPC_EXCL);
			ch[i] = (char *) malloc(sizeof (char) * N);
			ch[i] = readf(a[i + 1], &s);
			buf.mtype = 1;
			buf.mSum[i] = calcSumm(ch, i, s);
			//printf("Summa = %d \n", buf.mSum[i]);
			int n = msgsnd(msqid, &buf, sizeof (buf.mSum), 0);
			int u = msgrcv(msqid, &test,sizeof (struct msgbuf) - sizeof (long), buf.mtype, IPC_NOWAIT);
			printf("stat1 %d stat2 %d = %d \n", n, u, test.mSum[i]);
			exit(0);
		}
		wait(pid);
	}

	msqid = msgget(0, 0600);
	//printf("%d %d\n", msqid, IPC_PRIVATE);
	fflush(stdout);

	for (int i = 0; i < argc - 1; i++)
	{
		int n = msgrcv(msqid, &test, sizeof (struct msgbuf) - sizeof (long), buf.mtype, MSG_NOERROR);
		printf("Read %d bytes = %d \n", n, test.mSum[i]);
	}

	for (int i = 0; i < argc - 1; i++)
	{
		printf("Control summ in file %s = %d\n", argv[i + 1], sum[i]);
	}

	free(ch);

	for (int i = 1; i < argc - 1; i++)
	{
		fclose(a[i]);
	}

	return 0;
}
