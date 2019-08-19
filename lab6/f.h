#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024
#define BUF "buf.txt"

char** readf(FILE *fr, int *s); //чтение из файла массива строк

char** Del_end(char **mas, int s);//удаление символа новой строки

void search(char **mas, int c, char *b);//поиск слова

void fork_search(char **ch, int s, char *b); //поиск слова

void printMas(char **mas, int *count); //вывод массива

void freeMas(char **mas); //очистка массива
