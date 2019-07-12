/*
 ============================================================================
 Name        : lab6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define N 1024


int main(int argc, char *argv[])
{

	FILE *fr;
	char s1[1024];
	char **ch = NULL;
	int s = 0;

	if((fr=fopen(argv[1],"a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}

	strcpy(s1, argv[2]);


	ch = readf(fr, &s);
	search(ch, &s, s1);
//	outf(fu, ch, buf, &s);
	freeMas(ch);

  	fclose(fr);

	return 0;
}
