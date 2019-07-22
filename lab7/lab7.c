#include "f.h"
#define N 1024

int main(int argc, char *argv[])
{
	FILE *fr;
	char sd[1024];
	int **mat = NULL;
	char **mas = NULL;
	char *v = NULL;
	int *vec = NULL;
	int *res_v = NULL;
	int s = 0, //число строк матрицы		
		p = 0, //число элементов вектора
		n = 0; //число столбцов матрицы
			
	if((fr=fopen(argv[1],"a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}
		
	mas = read_mas(fr, &s);
	
	fclose(fr);
	
	if((fr=fopen(argv[2],"a+"))==NULL)
	{
		printf("Невозможно открыть файл для чтения.\n");
		exit(1);
	}
		
	v = read_vec(fr);
	
	fclose(fr);
	
	vec = ToVec(v, &n);
	
	for(int i =0; i < n; i++)
	{
		printf("VEC = %d\n", vec[i]);
	}
								
	mat = ToInt(mas, s, &p);
	
	print_mat(mat, s, p);
	
	if(p == n)
	{	
		res_v = mult_M_V(mat, vec, s, p);
		out_vec(res_v, p);
	}
	else
		printf("Нельзя перемножить вектор и матрицу. Число столбцов должно быть равно числу элементов вектора");
	
	freeMas(mas);
	freeVec(v);
	freeMasI(mat, s);
	freeVecI(vec);
	
	return 0;
}
