#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/errno.h>
#include <unistd.h>

#define N 1024



char * readf(FILE *fr, int *s); //получение массива символов из файла

int calcSumm(char **ch, int i, int s); //вычисление контрольной суммы (сумма кодов всех ситмволов в файле)

void printMas(char *mas, int *count); //вывод массива (вдруг нужно)

void freeMas(char **mas); //очистка двумерного массива массива

void freeMassm(char *mas); //очистка массива символов

void outf(FILE *fu, char *ch, char *b, int *s); //запись обработанного массива символов в файл
