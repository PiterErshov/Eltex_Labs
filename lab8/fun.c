#include "prot.h"

char *readf(FILE * fr, int *s)	//получение массива символов из файла
{
	int i = 0;
	char b;
	char *ch;
	ch = malloc(sizeof (char) * N);

	while (!feof(fr))
	{
		b = fgetc(fr);
		ch[i] = b;
		i++;
	}
	*s = i - 1;
	return ch;
	free(ch);
}

int calcSumm(char **ch, int i, int s)	//вычисление суммы для одного файла
{
	int sum = 0;
	for (int j = 0; j < s; j++)
		sum += ch[i][j];
	return sum;
}

void process_file(char **ch, int msqid, int argc, char *argv[])	//обработка всех файлов
{
	int s = 0;
	pid_t pid;
	FILE *fr;
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
			if ((fr = fopen(argv[i + 1], "r")) == NULL)
			{
				printf("Невозможно открыть файл для чтения.\n");
				exit(1);
			}
			else
				printf("file's name: %s\n", argv[i + 1]);

			ch[i] = malloc(sizeof (char) * N);
			ch[i] = readf(fr, &s);
			fclose(fr);
			buf.mtype = 1;
			buf.mSum[i] = calcSumm(ch, i, s);
			free(ch[i]);
			msgsnd(msqid, &buf, sizeof (buf.mSum), 0);
			exit(0);
		}
		wait(pid);
	}
}

void printMas(char *mas, int *count)	//вывод массива
{
	for (int i = 0; i < *count; i++)
	{
		printf("\n");
		printf("%c", mas[i]);
		printf("\n");
	}
}
