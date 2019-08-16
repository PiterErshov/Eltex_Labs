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
	freeMasI(m, s);
}

int checksum(int *mas, int n)
{
	int buf = 0;
	for(int i = 0; i < n; i++)
		buf += mas[i];
	if(buf == 100)
		return 1;
	else
		return 0;
}

void *M_x(void *arg)
{
	int i = *(int *) arg, s = 0, p = 0;
	char **mas = NULL;
	int **mat = NULL;
	int M = 0;
	FILE *fl;
	if ((fl = fopen(file_name[i], "r")) == NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}
	mas = read_mas(fl, &s);	
	fclose(fl);
	pthread_mutex_lock(&mutex);
	mat = ToInt(mas, s, &p);
	if(checksum(mat[1], p))
	{	
		for(int j = 0; j < p; j++)
			M += mat[0][j] * mat[1][j];
		printf("Математическое ожидание дискретной случайной величны из файла %s = %d\n", file_name[i], M);
	}
	else
	{
		printf("Некорректный формат дискретной случайной величины\n");
		printf("Сумма вероятностей должна равнятся 100\n");
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	}
	freeMas(mas);
	freeMasI(mat, s);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void printMas(char **mas, int *count)	//вывод массива
{
	for (int i = 0; i < *count; i++)
	{
		printf("%s\n", mas[i]);
	}
}

void print_mat(int **mas, int n, int m)	//вывод матрицы
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf(" %d ", mas[i][j]);
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
