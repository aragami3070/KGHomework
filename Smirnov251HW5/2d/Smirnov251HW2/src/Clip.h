#pragma once
#include "Matrix.h"
#include <algorithm>
unsigned int codeKS(vec2 P, float minX, float minY, float maxX, float maxY) {
	// Заготовка для кода точки
	unsigned int code = 0;
	
	// Дальнейшие комментарии предполагают, чтосистема координат правая
	if (P.x < minX) { // Точка левее области видимости
		code += 1; // Получаем единицу в первом разряде
	}
	else if (P.x > maxX) { // Точка правее области видимости
		code += 2; // Получаем единицу во втором разряде
	}
	if (P.y < minY) { // Точка ниже области видимости
		code += 4; // Получаем единицу в третьем разряде
	}
	else if (P.y > maxY) { // Точка ниже области видимости
		code += 8; // Получаем единицу в четвертом разряде
	}
	return code;
}

bool clip(vec2& A, vec2& B, float minX, float minY, float maxX, float maxY) {
	unsigned int codeA = codeKS(A, minX, minY, maxX, maxY); // Код области точки A
	unsigned int codeB = codeKS(B, minX, minY, maxX, maxY); // Код области точки B
	while (codeA | codeB) {
		if (codeA & codeB) { // Поразрядное И не равно нулю
			return false; // Отрезок полностью невидим
		}
		if (codeA == 0) { // Если А видима, то В невидима
			std::swap(A, B); // Меняем местами A и B
			std::swap(codeA, codeB); // меняем местами их коды
		}
		// Вычисляем новые координаты точки A
		if (codeA & 1) { // Точка А левее области видимости
			A.y = A.y + (B.y - A.y) * (minX - A.x) / (B.x - A.x);
			A.x = minX;
		}
		else if (codeA & 2) { // Точка А правее области видимости
			A.y = A.y + (B.y - A.y) * (maxX - A.x) / (B.x - A.x);
			A.x = maxX;
		}
		else if (codeA & 4) { // Точка А ноже области видимости
			A.x = A.x + (B.x - A.x) * (minY - A.y) / (B.y - A.y);
			A.y = minY;
		}
		else { // Точка А выше области видимости
			A.x = A.x + (B.x - A.x) * (maxY - A.y) / (B.y - A.y);
			A.y = maxY;
		}
		// Обновляем код области для точки A
		codeA = codeKS(A, minX, minY, maxX, maxY);
	}
	return true;
}

