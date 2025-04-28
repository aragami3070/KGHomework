#pragma once
#include <math.h>
class vec3;
class vec4;

// VEC 2

class vec2 {
  public:
    float x, y;
    // Конструкторы
    vec2() {
    }
    vec2(float a, float b) : x(a), y(b) {
    }

    vec2(vec3 v);

    ~vec2() {
    }

    // Умножение векторов *=
    // НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
    // просто умножение (как на коэффициент)
    vec2 &operator*=(const vec2 &v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    // Умножение векторов *
    // НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
    // просто умножение (как на коэффициент)
    const vec2 operator*(const vec2 &v) {
        // Делаем временную копию текущего объекта, которую домножаем на данный
        // вектор, и возвращаем ее как результат
        return vec2(*this) *= v;
    }

    // Перегрузка []
    float &operator[](int i) {
        // Ссылку на текущий объект рассматриваем как ссылку на нулевой элемент
        // массива значений типа float, после обращаемся к его i-му элементу
        return ((float *)this)[i];
    }
};
// Скалярное произведение векторов
float dot(vec2 v1, vec2 v2) {
    // Вычисляем произведения соответствующих координат
    vec2 tmp = v1 * v2;
    // Возвращаем их сумму
    return tmp.x + tmp.y;
}

// VEC 3

class vec3 {
  public:
    float x, y, z;
    // Конструкторы
    vec3() {
    }
    vec3(float a, float b, float c) : x(a), y(b), z(c) {
    }
    vec3(vec2 v, float c) : vec3(v.x, v.y, c) {
    }

    vec3(vec4 v);
    ~vec3() {
    }

    vec3 &operator+=(const vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    const vec3 operator+(const vec3 &v) {
        // Делаем временную копию текущего объекта, которую прибавляем к данному
        // вектору, и возвращаем ее как результат
        return vec3(*this) += v;
    }
    vec3 &operator-=(const vec3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    const vec3 operator-(const vec3 &v) {
        // Делаем временную копию текущего объекта, которую вычиатем из данного
        // вектору, и возвращаем ее как результат
        return vec3(*this) -= v;
    }

    // Умножение векторов *=
    // НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
    // просто умножение (как на коэффициент)
    vec3 &operator*=(const vec3 &v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    vec3 &operator*=(const float &n) {
        (*this) *= vec3(n, n, n); // Создаем вектор из трех копий числа и
                                  // домножаем на него исходный вектор
        return *this;
    }

    const vec3 operator*(const float &n) {
        return vec3(*this) *= n;
    }

    // Умножение векторов *
    // НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
    // просто умножение (как на коэффициент)
    const vec3 operator*(const vec3 &v) {
        // Делаем временную копию текущего объекта, которую домножаем на данный
        // вектор, и возвращаем ее как результат
        return vec3(*this) *= v;
    }

    // Перегрузка []
    float &operator[](int i) {
        // Ссылку на текущий объект рассматриваем как ссылку на нулевой элемент
        // массива значений типа float, после обращаемся к его i-му элементу
        return ((float *)this)[i];
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

// VEC 4

class vec4 {
  public:
    float x, y, z, a;
    // Конструкторы
    vec4() {
    }
    vec4(float a, float b, float c, float d) : x(a), y(b), z(c), a(d) {
    }
    vec4(vec3 v, float c) : vec4(v.x, v.y, v.z, c) {
    }
    ~vec4() {
    }

    // Умножение векторов *=
    // НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
    // просто умножение (как на коэффициент)
    vec4 &operator*=(const vec4 &v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        a *= v.a;
        return *this;
    }

    // Умножение векторов *
    // НЕ ВЕКТОРНОЕ И НЕ СКАЛЯРНОЕ
    // просто умножение (как на коэффициент)
    const vec4 operator*(const vec4 &v) {
        // Делаем временную копию текущего объекта, которую домножаем на данный
        // вектор, и возвращаем ее как результат
        return vec4(*this) *= v;
    }

    // Перегрузка []
    float &operator[](int i) {
        // Ссылку на текущий объект рассматриваем как ссылку на нулевой элемент
        // массива значений типа float, после обращаемся к его i-му элементу
        return ((float *)this)[i];
    }
};
// Скалярное произведение векторов
float dot(vec4 v1, vec4 v2) {
    // Вычисляем произведения соответствующих координат
    vec4 tmp = v1 * v2;
    // Возвращаем их сумму
    return tmp.x + tmp.y + tmp.z + tmp.a;
}

vec3 normalize(vec4 v) {
    // делим первые три координаты на значение четвертой
    return vec3(v.x / v.a, v.y / v.a, v.z / v.a);
}

vec2::vec2(vec3 v) : x(v.x), y(v.y) {
}
vec3::vec3(vec4 v) : x(v.x), y(v.y), z(v.z) {
}

// MAT 4

class mat4 {
  public:
    vec4 row1, row2, row3, row4;
    // Конструкторы
    mat4() {
    }
    mat4(vec4 r1, vec4 r2, vec4 r3, vec4 r4)
        : row1(r1), row2(r2), row3(r3), row4(r4) {
    }
    mat4(float a) {
        row1 = vec4(a, 0.f, 0.f, 0.f);
        row2 = vec4(0.f, a, 0.f, 0.f);
        row3 = vec4(0.f, 0.f, a, 0.f);
        row4 = vec4(0.f, 0.f, 0.f, a);
    }

    ~mat4() {
    }

    // Перегрузка []
    vec4 &operator[](int i) {
        // Массив значений типа vec4
        return ((vec4 *)this)[i];
    }

    // Транспонирование
    mat4 transpose() {
        // Делаем временную копию матрицы
        mat4 tmp(*this);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // Заменяем элементы текущего объекта их временной копии
                (*this)[i][j] = tmp[j][i];
            }
        }
        return *this;
    }

    // Умножение матрицы на вектор
    const vec4 operator*(const vec4 &v) {
        // Создаем новый вектор (для результата)
        vec4 *res = new (vec4);
        for (int i = 0; i < 4; i++) {
            // i-й элемент вектора - скалярное произведение
            (*res)[i] = dot((*this)[i], v);
        }
        return *res;
    }

    // Произведение матриц *=
    const mat4 &operator*=(const mat4 &m) {
        // Создаем копии исходных матриц
        mat4 A(*this), B(m);
        // Транспонируем вторую
        B.transpose();
        for (int i = 0; i < 4; i++) {
            // В i-ю строку текущего объекта записываем результат перемножения
            // первой матрицы с i-q строкой транспонированной матрицы
            (*this)[i] = A * B[i];
        }
        // Транспонируем текущий объект, получаем результат
        return (*this).transpose();
    }

    // Произведение матриц *=
    const mat4 operator*(const mat4 &m) {
        return mat4(*this) *= m;
    }
};

// MAT 3

class mat3 {
  public:
    vec3 row1, row2, row3;
    // Конструкторы
    mat3() {
    }
    mat3(vec3 r1, vec3 r2, vec3 r3) : row1(r1), row2(r2), row3(r3) {
    }
    mat3(float a) {
        row1 = vec3(a, 0.f, 0.f);
        row2 = vec3(0.f, a, 0.f);
        row3 = vec3(0.f, 0.f, a);
    }

    mat3(mat4 m) {
        row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
        row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
        row3 = vec3(m.row3.x, m.row3.y, m.row3.z);
    }

    ~mat3() {
    }

    // Перегрузка []
    vec3 &operator[](int i) {
        // Массив значений типа vec3
        return ((vec3 *)this)[i];
    }
    // Сложение матриц +=
    mat3 &operator+=(const mat3 &m) {
        // Создаем копию прибавляемой матрицы
        mat3 B(m);
        for (int i = 0; i < 3; i++) {
            (*this)[i] += B[i];
        }
        return (*this);
    }
    // Сложение матриц +=
    mat3 &operator+(const mat3 &m) {
        return mat3(*this) += m;
    }

    mat3 &operator*=(const float &n) {
        // Создаем копию прибавляемой матрицы
        for (int i = 0; i < 3; i++) {
            (*this)[i] *= n;
        }
        return (*this);
    }

    mat3 &operator*(const float &n) {
        return mat3(*this) *= n;
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
    const vec3 operator*(const vec3 &v) {
        // Создаем новый вектор (для результата)
        vec3 *res = new (vec3);
        for (int i = 0; i < 3; i++) {
            // i-й элемент вектора - скалярное произведение
            (*res)[i] = dot((*this)[i], v);
        }
        return *res;
    }

    // Произведение матриц *=
    const mat3 &operator*=(const mat3 &m) {
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
    const mat3 operator*(const mat3 &m) {
        return mat3(*this) *= m;
    }
};
// Матрица первого множителя векторного произведения
mat3 crossM(vec3 p) {
    return mat3(vec3(0.f, -p.z, p.y), vec3(p.z, 0.f, -p.x),
                vec3(-p.y, p.x, 0.f));
}

vec3 cross(vec3 p, vec3 q){
    return crossM(p) * q;
}

float length(vec3 p){
    return sqrtf(dot(p, p));
}

// Нормализация вектора p
vec3 norm(vec3 p){
    return normalize(vec4(p, length(p)));
}

// MAT 2

class mat2 {
  public:
    vec2 row1, row2;
    // Конструкторы
    mat2() {
    }
    mat2(vec2 r1, vec2 r2) : row1(r1), row2(r2) {
    }
    mat2(float a) {
        row1 = vec2(a, 0.f);
        row2 = vec2(0.f, a);
    }

    // Конструкстор из mat3 в mat2, через отсечение последние строки и
    // последнего столбца
    mat2(mat3 m) {
        row1 = vec2(m[0][0], m[0][1]);
        row2 = vec2(m[1][0], m[1][1]);
    }

    ~mat2() {
    }

    // Перегрузка []
    vec2 &operator[](int i) {
        // Массив значений типа vec2
        return ((vec2 *)this)[i];
    }

    // Транспонирование
    mat2 transpose() {
        // Делаем временную копию матрицы
        mat2 tmp(*this);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                // Заменяем элементы текущего объекта их временной копии
                (*this)[i][j] = tmp[j][i];
            }
        }
        return *this;
    }

    // Умножение матрицы на вектор
    const vec2 operator*(const vec2 &v) {
        // Создаем новый вектор (для результата)
        vec2 *res = new (vec2);
        for (int i = 0; i < 2; i++) {
            // i-й элемент вектора - скалярное произведение
            (*res)[i] = dot((*this)[i], v);
        }
        return *res;
    }

    // Произведение матриц *=
    const mat2 &operator*=(const mat2 &m) {
        // Создаем копии исходных матриц
        mat2 A(*this), B(m);
        // Транспонируем вторую
        B.transpose();
        for (int i = 0; i < 2; i++) {
            // В i-ю строку текущего объекта записываем результат перемножения
            // первой матрицы с i-q строкой транспонированной матрицы
            (*this)[i] = A * B[i];
        }
        // Транспонируем текущий объект, получаем результат
        return (*this).transpose();
    }

    // Произведение матриц *=
    const mat2 operator*(const mat2 &m) {
        return mat2(*this) *= m;
    }
};
