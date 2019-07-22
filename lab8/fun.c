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

int calcSumm(char **ch, int i, int s)
{
	int sum = 0;
	for(int j = 0; j < s; j++)
	{
		sum += ch[i][j];
	}
	return sum;
}

void printMas(char *mas, int *count) //вывод массива (вдруг нужно)
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

void freeMas(char **mas) //очистка массива
{
	for (int i = 0; i < N; i++)
	{
      		free(mas[i]);
   	}
	free(mas);
}

void outf(FILE *fu, char *ch, char *b, int *s) //запись обработанного массива символов в файл
{
	for (int i = 0; i < *s; i++)
	{
		if (ch[i] != b[0])
		{
			printf("%c", ch[i]);
			fputc(ch[i], fu);
		}
	}
}

