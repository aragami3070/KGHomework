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
	const vec3 operator *(const vec3& v) {
		// Делаем временную копию текущего объекта, которую домножаем на данный вектор,
		// и возвращаем ее как результат
		return vec3(*this) *= v; 
	}

	// Перегрузка []
	float& operator [](int i) {
		// Ссылку на текущий объект рассматриваем как ссылку на нулевой элемент
		// массива значений типа float, после чего обращаемся к его i-му элементу
		return ((float*)this)[i];
	}
};
// Скалярное произведение векторов
float dot(vec3 v1, vec3 v2) {
	// Вычисляем произведения соответствующих координат
	vec3 tmp = v1 * v2;
	// Возвращаем их сумму
	return tmp.x + tmp.y + tmp.z;
}

// Переход из однородных координат в евклидовы
vec2 normalize(vec3 v) {
	return vec2(v.x / v.z, v.y / v.z);
}

class mat3
{
public:
	vec3 row1, row2, row3;
	// Конструкторы
	mat3() {}
	mat3(vec3 r1, vec3 r2, vec3 r3) : row1(r1), row2(r2), row3(r3) {}
	mat3(float a) {
		row1 = vec3(a, 0.f, 0.f);
		row2 = vec3(0.f, a, 0.f);
		row3 = vec3(0.f, 0.f, a);
	}

	~mat3() {}

	// Перегрузка []
	vec3& operator [](int i) {
		// Массив значений типа vec3
		return ((vec3*)this)[i];
	}

	// Транспонирование
	mat3 transpose() {
		// Делаем временную копию матрицы
		mat3 tmp(*this);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Заменяем элементы текущего объекта их временной копии
				(*this)[i][j] = tmp[j][i];
			}
		}
		return *this;
	}

	// Умножение матрицы на вектор
	const vec3 operator *(const vec3& v) {
		// Создаем новый вектор (для результата)
		vec3* res = new(vec3);
		for (int i = 0; i < 3; i++) {
			// i-й элемент вектора - скалярное произведение
			(*res)[i] = dot((*this)[i], v);
		}
		return *res;
	}

	// Произведение матриц *=
	mat3& operator *=(const mat3& m) {
		// Создаем копии исходных матриц
		mat3 A(*this), B(m);
		// Транспонируем вторую
		B.transpose();
		for (int i = 0; i < 3; i++) {
			// В i-ю строку текущего объекта записываем результат перемножения
			// первой матрицы с i-q строкой транспонированной матрицы
			(*this)[i] = A * B[i];
		}
		// Транспонируем текущий объект, получаем результат
		return (*this).transpose();
	}

	// Произведение матриц *=
	const mat3 operator *(const mat3& m) {
		return mat3(*this) *= m;
	}
};
