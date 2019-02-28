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

	float temp_p = 0;
	float temp_q = 0;

	printf("\n%s", "Стратегия игрока А: ");
	for (int j = 0; j < SIZE; j++)
	{
		A_strategy[j] = A_strategy[j] / temp;
		temp_p = temp_p + A_strategy[j];
		printf("\t%.3f", A_strategy[j]);
	}

	printf("\n\n%s", "Стратегия игрока В: ");
	for (int k = 0; k < SIZE; k++)
	{
		B_strategy[k] = B_strategy[k] / temp;
		temp_q = temp_q + B_strategy[k];
		printf("\t%.3f", B_strategy[k]);
	}

	if ((rint(temp_p) != 1) || (rint(temp_q) != 1))
		printf("\n\n%s\n", "Ошибка! Сумма вероятностей использования стратегий для каждого игрока должна быть равна единице!");
	printf("\n\n");

	float price = 1 / temp;
	printf("%s %.3f\n", "Цена игры: ", price);

	for (int k = 0; k < SIZE; k++)
	{
		if ((A_strategy[k] < 0) || (B_strategy[k] < 0))
		{
			printf("\n%s\n", "Аналитический метод не применим! Воспользуйтесь другим методом!");
			break;
		}
	}
	

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
	
	
