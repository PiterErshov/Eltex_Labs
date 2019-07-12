#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024


char** readf(FILE *fr, int *s) //чтение из файла массива строк
{
	int i = 0;
	char b[1024];
	char **ch;
	ch = (char **)malloc(sizeof(char *)*1024);
	while(!feof(fr))
	{
		fgets(b, 100, fr);
		ch[i] = (char *)malloc(sizeof(char)*N);
		strcpy(ch[i], b);
		i++;
	}
	*s = i - 1;
	return ch;
}

void search(char **mas, int *c, char *b)//поиск слова
{
	int f = 0, y = 0;
	for(int i = 0; i < *c; i++)
	{
		y = strcmp(mas[i], b[0]);
		if(y == 0)
		{
			f++;
		}
	}
	printf("Слово %s найдено %d раз", b[0], f);
}

void printMas(char **mas, int *count) //вывод массива
{
    	for (int i = 0; i < *count ; i++)
   	{
		printf("\n");
       		printf("%s", mas[i]);
       		printf("\n");
    	}
}


void freeMas(char **mas) //очистка массива
{
	for (int i = 0; i < 1024; i++)
	{
      		free(mas[i]);
   	}
	free(mas);
}

void outf(FILE *fu, char **ch, int buf, int *s) //вывод обработанного массива в файл
{

	char b[1024];
	for(int i = 0; i < *s; i++)
	{
		if(strlen(ch[i]) <= (buf + 1))
		{
			strcpy(b, ch[i]);
			printf("%s", ch[i]);
			fputs(b, fu);
		}
	}
}


