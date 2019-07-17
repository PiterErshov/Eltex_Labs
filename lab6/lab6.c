#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define N 1024


int main(int argc, char *argv[])
{

	FILE *fr;
	char s1[N];
	char **ch = NULL;
	int s = 0;
	if((fr=fopen(argv[1],"a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}

	strcpy(s1, argv[2]);
	
	//printf("%s", s1);
	
	ch = readf(fr, &s);		
  	fclose(fr);
  	
	ch = Del_end(ch, s);
	
	/*fork_search(ch, s, s1);

	if((fr=fopen("buf.txt","a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}
	wait(0);
	char b[N];
	fgets(b, 100, fr);
	int m = atoi(b);
	printf("Слово %s найдено %d раз \n", s1, m);
	//*/
	
	for(int i = 0; i < s; i++)
	{
		printf("String %i = %s\n", i, ch[i]);
	}
	
//	outf(fu, ch, buf, &s);
	freeMas(ch);


	return 0;
}
