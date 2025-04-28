#pragma once
#include "Matrix.h"
#include <cmath>
#include <math.h>

// �������������� ��������
mat3 translate(float Tx, float Ty) {
    // ������� ��������� �������
    mat3 *res = new mat3(1.f);
    // �������� �������� � ��������� �������
    (*res)[0][2] = Tx;
    (*res)[1][2] = Ty;
    return *res;
}

// �������������� ���������������
mat3 scale(float Sx, float Sy) {
    // ������� ��������� �������
    mat3 *res = new mat3(1.f);
    // �������� �������� �� ������� ���������
    (*res)[0][0] = Sx;
    (*res)[1][1] = Sy;
    return *res;
}

// �������������� ���������������, ��� Sx == Sy
mat3 scale(float S) {
    return scale(S, S);
}

// �������������� �������� ������� �������� ������������ ������ ��������� ��
// ���� theta
mat3 rotate(float theta) {
    // ������� ��������� �������
    mat3 *res = new mat3(1.f);
    // ��������� ������� ���������
    (*res)[0][0] = (*res)[1][1] = (float)cos(theta);
    // ����� � ������ ������ (� ������)
    (*res)[0][1] = (float)sin(theta);
    // ����� �� ������ ������ (� �������)
    (*res)[1][0] = -(*res)[0][1];
    return *res;
}

// �������������� �� Ox
mat3 mirrorX() {
    // ������� ��������� �������
    mat3 *res = new mat3(1.f);
    //
    (*res)[0][0] = 1.f;
    //
    (*res)[1][1] = -1.f;
    return *res;
}

// �������������� �� Oy
mat3 mirrorY() {
    // ������� ��������� �������
    mat3 *res = new mat3(1.f);
    //
    (*res)[0][0] = -1.f;
    //
    (*res)[1][1] = 1.f;
    return *res;
}

mat4 translate(float Tx, float Ty, float Tz) {
    // ������� ��������� �������
    mat4 *res = new mat4(1.f);
    // �������� �������� � ��������� �������
    (*res)[0][3] = Tx;
    (*res)[1][3] = Ty;
    (*res)[2][3] = Tz;
    return *res;
}
mat4 scale(float Sx, float Sy, float Sz) {
    // ������� ��������� �������
    mat4 *res = new mat4(1.f);
    // ��������
    // �������� �� ������� ���������
    (*res)[0][0] = Sx;
    (*res)[1][1] = Sy;
    (*res)[2][2] = Sz;
    return *res;
}

// �������������� ���������
mat4 rotate(float theta, vec3 n) {
    // ������� ��������� �������
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
