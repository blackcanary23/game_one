#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include "braun_robinson_method.h"
//#include "det.h"


int main(void)
{
	float** matrix; // указатель на указатель на строку элементов

	system("chcp 1251");
	system("cls");
	printf("Введите размерность квадратной матрицы: ");
	scanf("%d", &SIZE);

	// Выделение памяти под указатели на строки
	matrix = (float**)malloc(SIZE * sizeof(float*));
	// Ввод элементов массива
	for (int i = 0; i < SIZE; i++)  // цикл по строкам
	{
		// Выделение памяти под хранение строк
		matrix[i] = (float*)malloc(SIZE * sizeof(float));
		for (int j = 0; j < SIZE; j++)  // цикл по столбцам
		{
			printf("матрица[%d][%d] = ", i, j);
			scanf("%f", &matrix[i][j]);
		}
	}

	float game_number = 1;
	float lower_price;
	float upper_price;
	float average_price;
	float accuracy;


	static float* loss_of_B;
	static float* win_of_A;
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

	printf("\n%s\n\n", "1. Метод Брауна-Робинсон");
	printf("%s\t %s ", "Партия", "Номер стратегии А");
	for (int i = 0; i < SIZE; i++)
		printf("\t%s%d ", "B", i);
	printf("\t%s ", "Номер стратегии В");
	for (int j = 0; j < SIZE; j++)
		printf("\t%s%d ", "A", j);
	printf("\t%s \t%s \t%s \t%s\n", "Нижняя оценка", "Верхняя оценка", "Средняя цена игры", "Точность");
	do
	{
		search_of_min_element(matrix, ptrObjA, loss_of_B, ptrObjB);
		printf("%.0f \t %d \t\t\t", game_number, ptrObjA->strategy_number_of_A);
		for (int i = 0; i < SIZE; i++)
			printf("%.0f\t", loss_of_B[i]);
		printf("%d\t\t ", ptrObjB->strategy_number_of_B);
		search_of_max_element(matrix, ptrObjB, win_of_A, ptrObjA);
		lower_price = ptrObjB->min_element / game_number;
		upper_price = ptrObjA->max_element / game_number;
		average_price = (lower_price + upper_price) / 2;
		accuracy = upper_price - lower_price;
		for (int j = 0; j < SIZE; j++)
			printf("\t%.0f", win_of_A[j]);
		printf("\t%.3f \t\t%.3f \t\t%.3f \t\t\t%.3f\n", lower_price, upper_price, average_price, accuracy);
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


	printf("\n %s", "Счетчик стратегий игрока А: ");
	for (int j = 0; j < SIZE; j++)
		printf("%.0f ", p[j]);
	printf("\n %s", "Счетчик стратегий игрока В: ");
	for (int i = 0; i < SIZE; i++)
		printf("%.0f ", q[i]);

	for (int i = 0; i < SIZE; i++)
	{
		p[i] = p[i] / game_number;
		q[i] = q[i] / game_number;
	}

	float temp_p = 0;
	float temp_q = 0;

	printf("\n\n %s", "Стратегия игрока А: ");
	for (int j = 0; j < SIZE; j++)
	{
		temp_p = temp_p + p[j];
		printf("%.3f ", p[j]);
	}
	printf("\n %s", "Стратегия игрока В: ");
	for (int i = 0; i < SIZE; i++)
	{
		temp_q = temp_q + q[i];
		printf("%.3f ", q[i]);
	}

	if ((rint(temp_p) != 1) || (rint(temp_q) != 1))
		printf("\n\n%s\n", "Ошибка! Сумма вероятностей использования стратегий для каждого игрока должна быть равна единице!");
	printf("\n\n");


	//


	int det;
	det = compute_determinant(matrix, SIZE);

	if (det == 0)
		printf("\n\n%s\n\n", "Ошибка! Определитель равен нулю, обратной матрицы не существует!");

	printf("\n\n%s\n\n", "2. Аналитический метод");
	printf("%s\n", "Обратная матрица: ");
	compute_inverse_matrix(matrix, SIZE, det);

	
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