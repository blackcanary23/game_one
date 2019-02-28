#include <stdio.h>
#include <math.h>
#include "det.h"


// Получение матрицы без i-й строки и j-го столбца
 void get_matrix(float** matrix, float** new_matrix, int row, int column, int SIZE) {
	int di, dj;
	di = 0;
	for (int i = 0; i < SIZE - 1; i++) { // проверка индекса строки
		if (i == row) di = 1;
		dj = 0;
		for (int j = 0; j < SIZE - 1; j++) { // проверка индекса столбца
			if (j == column) dj = 1;
			new_matrix[i][j] = matrix[i + di][j + dj];
		}
	}
}
// Рекурсивное вычисление определителя
 int compute_determinant(float** matrix, int SIZE) {
	 int det, sign, new_SIZE;
	
	float **new_matrix;
	new_matrix = (float**)malloc(SIZE * sizeof(float*));
	for (int i = 0; i < SIZE; i++)  
		new_matrix[i] = (float*)malloc(SIZE * sizeof(float));
	

	det = 0;
	sign = 1; //(-1) в степени i
	new_SIZE = SIZE - 1;
	if (SIZE < 1) 
		printf("Определитель вычислить невозможно!");
	if (SIZE == 1) {
		det = matrix[0][0];
		return(det);
	}
	if (SIZE == 2) {
		det = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
		return(det);
	}
	if (SIZE > 2) {
		for (int i = 0; i < SIZE; i++) {
			get_matrix(matrix, new_matrix, i, 0, SIZE);
			det = det + sign * matrix[i][0] * compute_determinant(new_matrix, new_SIZE);
			sign = -sign;
		}
	}

	// Очистка памяти
	/*for (int j = 0; j < new_SIZE; j++)  // цикл по строкам
		free(new_matrix[j]);   // освобождение памяти под строку
	free(new_matrix);*/

	return(det);
}

