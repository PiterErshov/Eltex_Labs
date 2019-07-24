#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"

int main(int argc, char *argv[])
{
	FILE *fr;
	char s1[N], b[N];
	char **ch = NULL;
	int s = 0, f = 0, y = 0;
	char **ch1 = NULL;
	if((fr=fopen(argv[1],"a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}
	
	strcpy(s1, argv[2]);
	
	ch = readf(fr, &s);		
  	fclose(fr);
  	
	ch = Del_end(ch, s);		
	fork_search(ch, s, s1);
		
	if((fr=fopen(BUF,"a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}

	fgets(b, N, fr);
	printf("Слово %s найдено %d раз \n", s1, atoi(b));

	freeMas(ch);
	return 0;
}
