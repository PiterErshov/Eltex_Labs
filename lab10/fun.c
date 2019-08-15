#include "prot.h"

char **read_mas(FILE * fr, int *s)	//чтение из файла массива строк
{
	int i = 0;
	char b[N];
	char **ch;
	ch = (char **) malloc(sizeof (char *) * N);
	while (!feof(fr))
	{
		fgets(b, N, fr);
		if (b[0] != '\n' )
		{
			ch[i] = (char *) malloc(sizeof (char) * N);
			strcpy(ch[i], b);
			i++;
		}
	}
	printMas(ch, &i);
	*s = i;
	return ch;
	freeMas(ch);
}

int **ToInt(char **mas, int s, int *p)	// из строкового массива в числовую матрицу
{
	int **m;
	int n = 0;
	m = (int **) malloc(sizeof (int *) * s);

	for (int i = 0; i < s; i++)
	{
		n = 0;
		int k = 0, t = 0;
		char buf[N] = "";

		while (k < strlen(mas[i]) - 1)
		{
			if (mas[i][k] == ' ')
				n++;
			k++;
		}

		n++;
		*p = n;
		m[i] = (int *) malloc(sizeof (int) * n);

		n = 0;
		k = 0;
		while (k < strlen(mas[i]))
		{
			if (mas[i][k] == ' ' || k == strlen(mas[i]) - 1)
			{
				m[i][n] = atoi(buf);
				t = 0;
				memset(buf, 0, N);
				n++;
			}
			else
			{
				buf[t] = mas[i][k];
				t++;
			}
			k++;
		}
	}
	return m;
	freeMasI(m, n);
}

void *M_x(void *arg)
{
	int i = *(int *) arg, s = 0;
	char **mas = NULL;
	int **mat = NULL;
	FILE *fl;
	if ((fl = fopen(file_name[i], "r")) == NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}
	mas = read_mas(fl, &s);	
	
	pthread_mutex_lock(&mutex);
	
	printMas(mas, &s);
	
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void printMas(char **mas, int *count)	//вывод массива
{
	for (int i = 0; i < *count; i++)
	{
		printf("\n");
		printf("%s", mas[i]);
		printf("\n");
	}
}

void freeMas(char **mas)	//очистка массива
{
	for (int i = 0; i < 1024; i++)
		free(mas[i]);
	free(mas);
}

void freeMasI(int **mas, int n)	//очистка матрицы
{
	for (int i = 0; i < n; i++)
		free(mas[i]);
	free(mas);
}
