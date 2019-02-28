#include <stdio.h>
#include <math.h>
#include "det.h"



int compute_inverse_matrix(float** matrix, int SIZE, int main_det)
{
	int new_SIZE;
	new_SIZE = SIZE - 1;
	float sign = 1;
	int det;

	float **matr;
	matr = (float**)malloc(SIZE * sizeof(float*));
	for (int i = 0; i < SIZE; i++)
		matr[i] = (float*)malloc(SIZE * sizeof(float));

	float **inv_matr;
	inv_matr = (float**)malloc(SIZE * sizeof(float*));
	for (int i = 0; i < SIZE; i++)
		inv_matr[i] = (float*)malloc(SIZE * sizeof(float));
	

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			get_matrix(matrix, matr, i, j, SIZE);
			det = compute_determinant(matr, new_SIZE);
			inv_matr[j][i] = sign * det / main_det;
			sign = -sign;
			//printf("%.0f\t", new_matrix[i][j]);
		}
		//printf("\n");
	}

	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%.3f\t", inv_matr[i][j]);
		}
		printf("\n");
	}
	
	//printf("%d\t", main_det);

	// Очистка памяти
		for (int j = 0; j < SIZE; j++)  // цикл по строкам
			free(matr[j]);   // освобождение памяти под строку
	free(matr);

	for (int j = 0; j < SIZE; j++)  // цикл по строкам
		free(inv_matr[j]);   // освобождение памяти под строку
	free(inv_matr);
	
	return 0;
}
