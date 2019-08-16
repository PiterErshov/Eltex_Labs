#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define N 1024


	pthread_mutex_t mutex;

char **file_name;

char** read_mas(FILE *fr, int *s);//чтение из массива строк

int** ToInt(char **mas, int s, int *p); // из строкового массива в числовую матрицу

void *M_x(void *arg);

void printMas(char **mas, int *count);	//вывод массива

void print_mat(int **mas, int n, int m);//вывод матрицы

int checksum(int *mas, int n);//проверка суммы вероятностей

void freeMas(char **mas); //очистка массива

void freeMasI(int **mas, int n) ; //очистка массива
