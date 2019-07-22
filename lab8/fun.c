#include "prot.h"

char * readf(FILE *fr, int *s) //получение массива символов из файла
{
	int i = 0;
	char b;
	char *ch;
	ch = (char *) malloc(sizeof(char) * N);
	
	while (!feof(fr))
	{
		b = fgetc(fr);
		ch[i] = b;
		i++;
	}
	*s = i - 1;
	return ch;
	freeMassm(ch);
}

int calcSumm(char **ch, int i, int s)//вычисление суммы для одного файла
{
	int sum = 0;
	for(int j = 0; j < s; j++)
		sum += ch[i][j];
	return sum;
}

void process_file(FILE **a, char **ch, int msqid, int argc)//обработка всех файлов
{	
	int s = 0;
	pid_t pid;
	struct msgbuf test;
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
			ch[i] = (char *) malloc(sizeof (char) * N);
			ch[i] = readf(a[i + 1], &s);
			buf.mtype = 1;
			buf.mSum[i] = calcSumm(ch, i, s);
			msgsnd(msqid, &buf, sizeof (buf.mSum), 0);
			exit(0);
		}
		wait(pid);
	}
}

void printMas(char *mas, int *count) //вывод массива
{
	for (int i = 0; i < *count; i++)
	{
		printf("\n");
		printf("%c", mas[i]);
		printf("\n");
	}
}

void freeMassm(char *mas) //очистка массива
{
	free(mas);
}
