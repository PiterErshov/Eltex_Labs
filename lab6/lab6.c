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
	char **ch1 = NULL;
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
	
	int f = 0, y = 0;
		
	//если очищать файл, то после всех операций с поиском заданной строки, не удаётся получить данные из файла buf.txt
	fr = fopen("buf.txt","w");
	fclose(fr);
	
	for(int i= 0; i < s - 1; i++)
	{
		
		pid_t pid;
		pid = fork();
		//search(ch, s, &s1);
		if (-1 == pid) 
		{
			perror("fork"); /* произошла ошибка */
			exit(1); 
		}
		
		if (0 == pid)
		{
			if((fr=fopen("buf.txt","a+"))==NULL)
			{
				printf("Невозможно открыть файл для чтения.\n");
				exit(1);
			}
			
			y = strcmp(ch[i], s1);
			strcpy(s1, "");
			
			
			if(y == 0)
			{		
				char b[N]="";
				fgets(b, N, fr);		
				
				fr = fopen("buf.txt","w");
				fclose(fr);
				
				fr = fopen("buf.txt","a+");				
				f = atoi(b); 
				f+=1;
				sprintf(b, "%d", f);				
				fputs(b, fr);
				fclose(fr);
			}			
			exit(0);	
			
		}		
	}
	
	if((fr=fopen("buf.txt","a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}
			
	char b[N];
	fgets(b, 100, fr);//не читает из файла и совершенно не понятно почему
	printf("Слово %s найдено %s раз \n", s1, atoi(b));
//	outf(fu, ch, buf, &s);
	freeMas(ch);


	return 0;
}
