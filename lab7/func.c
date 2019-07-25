#include "f.h"

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

char *read_vec(FILE * fr)	//чтение из файла строки
{
	char *ch;
	ch = (char *) malloc(sizeof (char) * N);
	fgets(ch, N, fr);
	return ch;
	free(ch);
}

int *ToVec(char *mas, int *p)	// из строки в числовой вектор
{
	int *m;
	int n = 0, k = 0, t = 0;
	char buf[N] = "";

	while (k < strlen(mas) - 1)
	{
		if (mas[k] == ' ')
		{
			n++;
		}
		k++;
	}

	n++;
	*p = n;
	m = (int *) malloc(sizeof (int) * n);

	n = 0;
	k = 0;
	while (k < strlen(mas))
	{
		if (mas[k] == ' ' || k == strlen(mas) - 1)
		{
			m[n] = atoi(buf);
			t = 0;
			memset(buf, 0, N);
			n++;
		}
		else
		{
			buf[t] = mas[k];
			t++;
		}
		k++;
	}
	return m;
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

int *mult_M_V(int **mat, int *vec, int n, int m)
{
	int *res;
	int K[2];

	res = (int *) calloc(n, sizeof (int));

	for (int i = 0; i < n; i++)
	{
		pipe(K);
		pid_t pid;

		pid = fork();
		if (-1 == pid)
		{
			perror("fork");
			exit(1);
		}

		if (0 == pid)
		{
			int buf = 0;
			for (int j = 0; j < m; j++)
				buf += mat[i][j] * vec[j];
			close(K[0]);
			write(K[1], &buf, sizeof (int));
			exit(0);
		}
		wait(pid);

		close(K[1]);
		read(K[0], &res[i], sizeof (int));
	}
	return res;
	free(res);
}

void out_vec(int *vec, int n)
{
	for (int i = 0; i < n; i++)
		printf("RES[%d] = %d\n", i, vec[i]);
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
