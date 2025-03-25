#pragma once
#include "Matrix.h"
#include <vector>

class path {
public:
	// Последовательность точек
	std::vector<vec2> vertices;
	// Цвет, разбитый на составляющие RGB
	vec3 color;
	// Толщина линии
	float thickness;

	path(std::vector<vec2> verts, vec3 col, float thickn) {
		vertices = verts;
		color = col;
		thickness = thickn;
	}
};
