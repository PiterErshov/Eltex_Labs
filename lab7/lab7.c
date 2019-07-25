#include "f.h"

int main(int argc, char *argv[])
{
	FILE *fr;
	char sd[N];
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
	out_vec(vec, n);
									
	mat = ToInt(mas, s, &p);	
	print_mat(mat, s, p);
	printf("s = %d\n", s);
	if(p == n)
	{	
		res_v = mult_M_V(mat, vec, s, p);
		out_vec(res_v, s);
	}
	else
		printf("Нельзя перемножить вектор и матрицу. Число столбцов должно быть равно числу элементов вектора");
	
	freeMas(mas);
	freeMasI(mat, s);
	free(v);
	free(vec);
	
	return 0;
}
