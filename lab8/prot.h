#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/errno.h>
#include <unistd.h>

#define N 1024

struct msgbuf
{
	long mtype;
	int mSum[N];
} buf;

char * readf(FILE *fr, int *s); //получение массива символов из файла

int calcSumm(char **ch, int i, int s); //вычисление контрольной суммы (сумма кодов всех ситмволов в файле)

void printMas(char *mas, int *count); //вывод массива (вдруг нужно)

void process_file(FILE **a, char **ch, int msqid, int argc); //обработка файлов

void freeMassm(char *mas); //очистка массива символов
