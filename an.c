#include <stdio.h>
#include <math.h>
#include "det.h"


void compute_strategies(float** inv_matr, int SIZE)
{

	float* A_strategy;
	A_strategy = (float*)malloc(SIZE * sizeof(float));
	float* B_strategy;
	B_strategy = (float*)malloc(SIZE * sizeof(float));

	for (int i = 0; i < SIZE; i++)
	{
		A_strategy[i] = 0;
		B_strategy[i] = 0;
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			A_strategy[i] = A_strategy[i] + inv_matr[j][i];
			B_strategy[i] = B_strategy[i] + inv_matr[i][j];
		}
	}

	float temp = 0;
	for (int i = 0; i < SIZE; i++)
	{
		temp = temp + A_strategy[i];
	}

	printf("\n%s", "Стратегия игрока А: ");
	for (int j = 0; j < SIZE; j++)
	{
		A_strategy[j] = A_strategy[j] / temp;
		printf("\t%.3f", A_strategy[j]);
	}

	printf("\n\n%s", "Стратегия игрока В: ");
	for (int k = 0; k < SIZE; k++)
	{
		B_strategy[k] = B_strategy[k] / temp;
		printf("\t%.3f", B_strategy[k]);
	}

	float price = 1 / temp;
	printf("\n\n%s %.3f\n", "Цена игры: ", price);

	free(A_strategy);
	free(B_strategy);

}



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
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%.3f\t", inv_matr[i][j]);
		}
		printf("\n");
	}

	compute_strategies(inv_matr, SIZE);

	// Очистка памяти
	for (int j = 0; j < SIZE; j++)  // цикл по строкам
		free(matr[j]);   // освобождение памяти под строку
	free(matr);

	for (int j = 0; j < SIZE; j++)  // цикл по строкам
		free(inv_matr[j]);   // освобождение памяти под строку
	free(inv_matr);

	return 0;
}
	
	
