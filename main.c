#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include "braun_robinson_method.h"
//#include "det.h"


int main(void)
{
	int** matrix; // указатель на указатель на строку элементов

	system("chcp 1251");
	system("cls");
	printf("Введите размерность квадратной матрицы: ");
	scanf("%d", &SIZE);

	// Выделение памяти под указатели на строки
	matrix = (int**)malloc(SIZE * sizeof(int*));
	// Ввод элементов массива
	for (int i = 0; i < SIZE; i++)  // цикл по строкам
	{
		// Выделение памяти под хранение строк
		matrix[i] = (int*)malloc(SIZE * sizeof(int));
		for (int j = 0; j < SIZE; j++)  // цикл по столбцам
		{
			printf("matrix[%d][%d] = ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}

	float game_number = 1;
	float lower_price;
	float upper_price;
	float average_price;
	float accuracy;


	static int* loss_of_B;
	static int* win_of_A;
	loss_of_B = (float*)malloc(SIZE * sizeof(float));
	win_of_A = (float*)malloc(SIZE * sizeof(float));
	
	for (int i = 0; i < SIZE; i++)
	{
		loss_of_B[i] = 0;
		win_of_A[i] = 0;
	}

	gamer_A objA;
	gamer_A* ptrObjA = &objA;
	gamer_B objB;
	gamer_B* ptrObjB = &objB;
	ptrObjA->strategy_number_of_A = 1; // пусть стратегия игрока А равна 1
	float* p;  // стратегии игрока А
	float* q; // стратегии игрока B

	 // Выделение памяти
	p = (float*)malloc(SIZE * sizeof(float));
	q = (float*)malloc(SIZE * sizeof(float));
	

	for (int j = 0; j < SIZE; j++)
	{
		p[j] = 0;
		q[j] = 0;
	}

	printf("\n%s\n\n", "1. Braun-Robinson Method");
	printf("%s\t %s ", "game_number", "strategy_number_of_A");
		for (int i = 0; i < SIZE; i++)
			printf("\t%s%d ", "B", i);
	printf("\t%s ", "strategy_number_of_B");
	    for (int j = 0; j < SIZE; j++)
		    printf("\t%s%d ", "A", j);
	printf("\t%s \t%s \t%s \t%s\n", "lower_price", "upper_price", "average_price", "accuracy");
	do
	{
		search_of_min_element(matrix, ptrObjA, loss_of_B, ptrObjB);
		printf("%.0f \t\t %d \t\t\t", game_number, ptrObjA->strategy_number_of_A);
		for (int i = 0; i < SIZE; i++)
			printf("%d\t", loss_of_B[i]);
		printf("%d\t\t ", ptrObjB->strategy_number_of_B);
		search_of_max_element(matrix, ptrObjB, win_of_A, ptrObjA);
		lower_price = ptrObjB->min_element / game_number;
		upper_price = ptrObjA->max_element / game_number;
		average_price = (lower_price + upper_price) / 2;
		accuracy = upper_price - lower_price;
		for (int j = 0; j < SIZE; j++)
			printf("\t%d", win_of_A[j]);
		printf("\t%.3f \t\t%.3f \t\t%.3f \t\t%.3f\n", lower_price, upper_price, average_price, accuracy);
		game_number++;

		for (int i = 0; i < SIZE; i++)
		{
			if (ptrObjA->strategy_number_of_A == (i + 1))
			{
	
				p[i] = p[i] + 1;
				break;
			}
		}

		for (int j = 0; j < SIZE; j++)
		{
			if (ptrObjB->strategy_number_of_B == (j + 1))
			{
				q[j] = q[j] + 1;
				break;
			}
		}


	} while (accuracy > 0.1);


	printf("\n %s", "Count of A gamer strategies: ");
		for (int j = 0; j < SIZE; j++)
		printf("%.0f ", p[j]);
	printf("\n %s", "Count of B gamer strategies: ");
		for (int i = 0; i < SIZE; i++)
		printf("%.0f ", q[i]);

	for (int i = 0; i < SIZE; i++)
	{
		p[i] = p[i] / game_number;
		q[i] = q[i] / game_number;
	}

	float temp_p = 0;
	float temp_q = 0;

	printf("\n %s", "A_strategy: ");
	for (int j = 0; j < SIZE; j++)
	{
		temp_p = temp_p + p[j];
		printf("%.3f ", p[j]);
	}
	printf("\n %s", "B_strategy: ");
	for (int i = 0; i < SIZE; i++)
	{
		temp_q = temp_q + q[i];
		printf("%.3f ", q[i]);
	}

	if ((rint(temp_p) != 1) || (rint(temp_q) != 1))
		printf("\n\n%s\n", "Ошибка! Сумма вероятностей использования стратегий для каждого игрока должна быть равна единице!");
	printf("\n\n");

	//

	/*int* vector;
	vector = (int*)malloc(SIZE * sizeof(int));

	for (int i = 0; i < SIZE; i++)
	{
		vector[i] = 1;
	}*/
	
	int det;
	det = compute_determinant(matrix, SIZE);
	printf("\n%d", det);
	
	if (det == 0)
		printf("\n\n%s\n\n", "Ошибка! Определитель равен нулю, обратной матрицы не существует!");

		printf("\n\n%s\n\n", "2. Analytical Method");
		printf("%s\n", "Inverse matrix: ");
		compute_inverse_matrix(matrix, SIZE, det);

/*		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				printf("%.4f\t\t", inv_matrix[i][j]);
			}
			printf("\n");
		}

		float gamerA_strategy[3];
		float* gamerA_strategy_ptr = gamerA_strategy;
		float gamerB_strategy[3];
		float* gamerB_strategy_ptr = gamerB_strategy;
		float game_price;
		float* game_price_ptr = &game_price;;

		printf("\n%s\t%s\n", "GamerA_strategy: ", "GamerB_strategy: ");
		compute_gamers_strategies(inv_matrix, vector_u, game_price_ptr, gamerA_strategy_ptr, gamerB_strategy_ptr);

		for (int k = 0; k < 3; k++)
		{
			printf("%.4f\t\t\t", gamerA_strategy[k]);
			printf("%.4f\n", gamerB_strategy[k]);
		}

		printf("\n%s %.4f\n", "Game_price: ", game_price);
		

		//

		*/







		// Очистка памяти
	for (int j = 0; j < SIZE; j++)  // цикл по строкам
		free(matrix[j]);   // освобождение памяти под строку
	free(matrix);

	free(p);
	free(q);
	free(loss_of_B);
	free(win_of_A);

	return 0;
}