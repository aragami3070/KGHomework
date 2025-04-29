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
    // Матрица вектора n
    mat3 res = crossM(norm(n));

    // Подсчет формулы родригеса
    res = (mat3)((mat3)(1.f) + (mat3)(res * sin(theta)) +
                 (mat3)((mat3)(res * res) * (float)(1 - cos(theta))));

    // Приводим к mat4 добавляя толбец из 3 нулей и строку из трех 0 и одной 1
    return mat4(vec4(res.row1, 0.f), vec4(res.row2, 0.f), vec4(res.row3, 0.f),
                vec4(0.f, 0.f, 0.f, 1.f));
}

mat4 rotateP(float theta, vec3 n, vec3 P) {
    return translate(P.x, P.y, P.z) *
           (rotate(theta, n) * translate(-P.x, -P.y, -P.z));
}

mat4 lookAt(vec3 S, vec3 P, vec3 u) {
    mat4 T = translate(-S.x, -S.y, -S.z);
    
    vec3 e3 = norm(S - P);
    vec3 e1 = norm(cross(u, e3));
    vec3 e2 = norm(cross(e3, e1));

    mat4 R = mat4(vec4(e1, 0.f), vec4(e2, 0.f), vec4(e3, 0.f),
                  vec4(0.f, 0.f, 0.f, 1.f));
    return R * T;
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

mat3 cadrRL(vec2 Vc, vec2 V, vec2 Wc, vec2 W) {
    return translate(Wc.x, Wc.y) *
           (scale(W.x / V.x, -W.y / V.y) * translate(-Vc.x, -Vc.y));
}
