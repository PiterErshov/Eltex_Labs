#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

char** read_mas(FILE *fr, int *s);//чтение из массива строк

char* read_vec(FILE *fr); //чтение из файла строки

int** ToInt(char **mas, int s, int *p); // из строкового массива в числовую матрицу

int* ToVec(char *mas, int *p);

int* mult_M_V(int **mat, int *vec, int n, int m);//умножение матрицы на вектор

void printMas(char **mas, int *count); //вывод массива;

void freeMas(char **mas); //очистка массива

void freeMasI(int **mas, int n) ; //очистка массива

void out_vec(int *vec, int n); //вывод вектора

void print_mat(int **mas, int n, int m);	//вывод матрицы
