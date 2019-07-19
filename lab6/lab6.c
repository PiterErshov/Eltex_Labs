
#include "f.h"
#define N 1024

int main (int argc, char *argv[])
{
	FILE *fr;
	char s1[N];
	char buf[N];
	char **ch = NULL;
	int s = 0;
	char **ch1 = NULL;
	if ((fr = fopen (argv[1], "a+")) == NULL)
	{
		printf ("Невозможно открыть файл для чтения.\n");
		exit (1);
	}

	strcpy (buf, argv[2]);
	strcpy (s1, argv[3]);

	ch = readf (fr, &s);
	fclose (fr);

	ch = Del_end (ch, s);

	int f = 0, y = 0;

	fork_search (buf, ch, s, s1);

	if ((fr = fopen (buf, "a+")) == NULL)
	{
		printf ("Невозможно открыть файл для чтения.\n");
		exit (1);
	}

	char b[N];
	fgets (b, 100, fr);
	int m = atoi (b);
	printf ("Слово %s найдено %d раз \n", s1, m);

	freeMas (ch);

	return 0;
}
