#pragma once
#include "Matrix.h"
#include <math.h>

// Преобразование переноса
mat3 translate(float Tx, float Ty) {
	// Создали единичную матрицу
	mat3* res = new mat3(1.f);
	// Поменяли значения в последнем столбце
	(*res)[0][2] = Tx;
	(*res)[1][2] = Ty;
	return *res;
}

// Преобразование масштабирования
mat3 scale(float Sx, float Sy) {
	// Создали единичную матрицу
	mat3* res = new mat3(1.f);
	// Поменяли значения на главной диагонали
	(*res)[0][0] = Sx;
	(*res)[1][1] = Sy;
	return *res;
}

// Преобразование масштабирования, где Sx == Sy
mat3 scale(float S) {
	return scale(S, S);
}

// Преобразование выдающее матрицу поворота относительно начала координат на угол theta
mat3 rotate(float theta) {
	// Создали единичную матрицу
	mat3* res = new mat3(1.f);
	// Заполнили главную диагональ
	(*res)[0][0] = (*res)[1][1] = (float)cos(theta);
	// Синус в первой строке (с плюсом)
	(*res)[0][1] = (float)sin(theta);
	// Синус во второй строке (с минусом)
	(*res)[1][0] = -(*res)[0][1];
	return *res;
}

// Отзеркаливание по Ox
mat3 mirrorX() {
	// Создали единичную матрицу
	mat3* res = new mat3(1.f);
	// 
	(*res)[0][0] = 1.f;
	// 
	(*res)[1][1] = -1.f;
	return *res;
	
}

// Отзеркаливание по Oy
mat3 mirrorY() {
	// Создали единичную матрицу
	mat3* res = new mat3(1.f);
	// 
	(*res)[0][0] = -1.f;
	// 
	(*res)[1][1] = 1.f;
	return *res;
	
}





