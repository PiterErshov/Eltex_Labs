#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024


<<<<<<< HEAD
char** readf(FILE *fr, int *s); //чтение из файла массива строк

char** Del_end(char **mas, int s);
=======
char** readf(FILE *fr, int *s) //чтение из файла массива строк
{
	int i = 0;
	char b[N];
	char **ch;
	ch = (char **)malloc(sizeof(char *)*N);
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

char** Del_end(char **mas, int s)
{
	for(int i = 0; i < s; i++)
	{
		mas[i] = strtok(mas[i], "\n");
	}	
	return mas;
}

void search(char **mas, int c, char *b)//поиск слова
{
	int f = 0, y = 0;
	for(int i = 0; i < c-1; i++)
	{
		y = strcmp(mas[i], b);
		if(y == 0)
		{
			f++;
		}
	}
	printf("Слово %s найдено %d раз \n", b, f);
}
>>>>>>> 2ef3bd19c4a0d123f04d921be467960d19593809

void search(char **mas, int c, char *b);//поиск слова

void fork_search(char **ch, int s, char *b); //поиск слова

<<<<<<< HEAD
void printMas(char **mas, int *count); //вывод массива
=======
void freeMas(char **mas) //очистка массива
{
	for (int i = 0; i < N; i++)
	{
      		free(mas[i]);
   	}
	free(mas);
}
>>>>>>> 2ef3bd19c4a0d123f04d921be467960d19593809

void freeMas(char **mas); //очистка массива

void outf(FILE *fu, char **ch, int buf, int *s); //вывод обработанного массива в файл


