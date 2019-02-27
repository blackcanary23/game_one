#include <stdio.h>
#include <math.h>
#include "det.h"



int compute_inverse_matrix(int** matrix, int SIZE, int main_det)
{
	int new_SIZE;
	new_SIZE = SIZE - 1;
	int sign = 1;
	int det;

	int **new_matrix;
	new_matrix = (int**)malloc(SIZE * sizeof(int*));
	for (int i = 0; i < SIZE; i++)
		new_matrix[i] = (int*)malloc(SIZE * sizeof(int));
	

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			get_matrix(matrix, new_matrix, i, j, SIZE);
			det = compute_determinant(new_matrix, new_SIZE);
			new_matrix[i][j] = sign * det;
			sign = -sign;
			//printf("%d\t", new_matrix[i][j]);
		}
		//printf("\n");
	}

	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			matrix[i][j] = new_matrix[j][i];
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}

	//printf("%d\t", main_det);

	// Очистка памяти
		for (int j = 0; j < SIZE; j++)  // цикл по строкам
			free(new_matrix[j]);   // освобождение памяти под строку
	free(new_matrix);
	
	return 0;
}
