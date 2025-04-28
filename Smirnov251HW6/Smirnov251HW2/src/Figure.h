#pragma once
#include "Matrix.h"
#include <vector>

class path {
public:
	// Последовательность точек
	std::vector<vec3> vertices;
	// Цвет, разбитый на составляющие RGB
	vec3 color;
	// Толщина линии
	float thickness;

	path(std::vector<vec3> verts, vec3 col, float thickn) {
		vertices = verts;
		color = col;
		thickness = thickn;
	}
};

class model {
public:
	// Состовляющие рисунка
	std::vector<path> figure;
	// Модельная матрица
	mat4 modelM;

	model(std::vector<path> fig, mat4 mat) {
		figure = fig;
		modelM = mat;
	}
};
