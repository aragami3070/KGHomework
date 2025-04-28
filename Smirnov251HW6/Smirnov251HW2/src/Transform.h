#pragma once
#include "Matrix.h"
#include <cmath>
#include <cstdlib>
#include <math.h>

// Преобразование переноса
mat3 translate(float Tx, float Ty) {
    // Создали единичную матрицу
    mat3 *res = new mat3(1.f);
    // Поменяли значения в последнем столбце
    (*res)[0][2] = Tx;
    (*res)[1][2] = Ty;
    return *res;
}

// Преобразование масштабирования
mat3 scale(float Sx, float Sy) {
    // Создали единичную матрицу
    mat3 *res = new mat3(1.f);
    // Поменяли значения на главной диагонали
    (*res)[0][0] = Sx;
    (*res)[1][1] = Sy;
    return *res;
}

// Преобразование масштабирования, где Sx == Sy
mat3 scale(float S) {
    return scale(S, S);
}

// Преобразование выдающее матрицу поворота относительно начала координат на
// угол theta
mat3 rotate(float theta) {
    // Создали единичную матрицу
    mat3 *res = new mat3(1.f);
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
    mat3 *res = new mat3(1.f);
    //
    (*res)[0][0] = 1.f;
    //
    (*res)[1][1] = -1.f;
    return *res;
}

// Отзеркаливание по Oy
mat3 mirrorY() {
    // Создали единичную матрицу
    mat3 *res = new mat3(1.f);
    //
    (*res)[0][0] = -1.f;
    //
    (*res)[1][1] = 1.f;
    return *res;
}

mat4 translate(float Tx, float Ty, float Tz) {
    // создали единичную матрицу
    mat4 *res = new mat4(1.f);
    // поменяли значения в последнем столбце
    (*res)[0][3] = Tx;
    (*res)[1][3] = Ty;
    (*res)[2][3] = Tz;
    return *res;
}
mat4 scale(float Sx, float Sy, float Sz) {
    // создали единичную матрицу
    mat4 *res = new mat4(1.f);
    // поменяли
    // значения на главной диагонали
    (*res)[0][0] = Sx;
    (*res)[1][1] = Sy;
    (*res)[2][2] = Sz;
    return *res;
}

// Преобразование Родригеса
mat4 rotate(float theta, vec3 n) {
    // Создали единичную матрицу
    mat3 *e = new mat3(1.f);

    (*e) += (mat3(vec3(0.f, -n.z, n.y), vec3(n.z, 0.f, -n.x),
                  vec3(-n.y, n.x, 0.f)) *
             sin(theta));

    (*e) += (mat3(vec3(-(n.z * n.z) - (n.y * n.y), n.x * n.y, n.x * n.z),
                  vec3(n.y * n.x, -(n.x * n.x) - (n.z * n.z), n.y * n.z),
                  vec3(n.z * n.x, n.z * n.y, -(n.x * n.x) - (n.y * n.y))) *
             (1 - cos(theta)));

    mat4 *res = new mat4(vec4(e->row1, 0.f), vec4(e->row2, 0.f),
                         vec4(e->row3, 0.f), vec4(0.f, 0.f, 0.f, 1.f));
    return (*res);
}

mat4 rotateP(float theta, vec3 n, vec3 P) {
    return translate(P.x, P.y, P.z) *
           (rotate(theta, n) * translate(-P.x, -P.y, -P.z));
}

mat4 lookAt(vec3 S, vec3 P, vec3 u) {
    mat4 T = mat4(vec4(1.f, 0.f, 0.f, -S.x), vec4(0.f, 1.f, 0.f, -S.y),
                  vec4(0.f, 0.f, 1.f, -S.z), vec4(0.f, 0.f, 0.f, 1.f));

    vec3 e3 = (S - P);
    float temp = sqrt(e3.x * e3.x + e3.y * e3.y + e3.z * e3.z);
    e3 *= (1 / temp);

    vec3 e1 = (cross(u, e3));
    temp = sqrt(e1.x * e1.x + e1.y * e1.y + e1.z * e1.z);
    e1 *= (1 / temp);

    vec3 e2 = (cross(e3, e1));
    temp = sqrt(e2.x * e2.x + e2.y * e2.y + e2.z * e2.z);
    e2 *= (1 / temp);

    mat4 *R = new mat4(vec4(e1, 0), vec4(e2, 0), vec4(e3, 0),
                       vec4(0.f, 0.f, 0.f, 1.f));

    (*R) *= T;
    return (*R);
}

mat4 ortho(float l, float r, float b, float t, float zn, float zf) {
    return mat4(vec4(2.f / (r - l), 0.f, 0.f, -(r + l) / (r - l)),
                vec4(0.f, 2.f / (t - b), 0.f, -(t + b) / (t - b)),
                vec4(0.f, 0.f, -2.f / (zf - zn), -(zf + zn) / (zf - zn)),
                vec4(0.f, 0.f, 0.f, 1.f));
}

mat4 frustum(float l, float r, float b, float t, float n, float f) {
    return mat4(vec4(2.f / (r - l), 0.f, (r + l) / (r - l), 0.f),
                vec4(0.f, 2.f / (t - b), (t + b) / (t - b), 0.f),
                vec4(0.f, 0.f, -(f + n) / (f - n), -2.f / (f - n)),
                vec4(0.f, 0.f, -1.f, 0.f));
}

mat4 perspective(float fovy, float aspect, float n, float f) {
    return mat4(vec4((1.f / aspect) * (1.f / tan(fovy / 2)), 0.f, 0.f, 0.f),
                vec4(0.f, (1.f / tan(fovy / 2)), 0.f, 0.f),
                vec4(0.f, 0.f, -(f + n) / (f - n), -2.f / (f - n)),
                vec4(0.f, 0.f, -1.f, 0.f));
}
