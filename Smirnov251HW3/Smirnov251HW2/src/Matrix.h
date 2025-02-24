#pragma once

class vec2 {
public:
	float x, y;
	// Конструкторы
	vec2 (){}
	vec2 (float a, float b) : x(a), y(b) {}

	~vec2 (){}
};

class vec3 {
public:
	float x, y, z;
	// Конструкторы
	vec3() {}
	vec3(float a, float b, float c) : x(a), y(b), z(c) {}
	vec3(vec2 v, float c) : vec3(v.x, v.y, c) {}
	~vec3() {}

	// Умножение векторов *=
	// НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
	// просто умножение (как на коэффициент)
	vec3& operator *= (const vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	// Умножение векторов *
	// НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
	// просто умножение (как на коэффициент)
	const vec3 operator * (const vec3& v) {
		// Делаем временную копию текущего объекта, которую домножаем на данный вектор,
		// и возвращаем ее как результат
		return vec3(*this) *= v; 
	}

	// Перегрузка []
	float& operator [] (int i) {
		// Ссылку на текущий объект рассматриваем как ссылку на нулевой элемент
		// массива значений типа float, после чего обращаемся к его i-му элементу
		return ((float*)this)[i];
	}
};
