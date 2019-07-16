#include "f.h"

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

void fork_search(char **ch, int s, char *b)//поиск слова
{
	int f = 0, y = 0;
	FILE *fr;
	
	fr = fopen("buf.txt","w");
	fclose(fr);
	
	for(int i= 0; i < s; i++)
	{		
		pid_t pid;
		pid = fork();
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
			
			y = strcmp(ch[i], b);
			strcpy(b, "");
						
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
		sleep(1);//ставим задержку, чтобы процесс успел завершиться
	}
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
	for (int i = 0; i < N; i++)
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

