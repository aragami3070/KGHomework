#pragma once

class vec2 {
public:
	float x, y;
	// ������������
	vec2 (){}
	vec2 (float a, float b) : x(a), y(b) {}

	~vec2 (){}
};

class vec3 {
public:
	float x, y, z;
	// ������������
	vec3() {}
	vec3(float a, float b, float c) : x(a), y(b), z(c) {}
	vec3(vec2 v, float c) : vec3(v.x, v.y, c) {}
	~vec3() {}

	// ��������� �������� *=
	// �� ��������� � �� ���������
	// ������ ��������� (��� �� �����������)
	vec3& operator *= (const vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	// ��������� �������� *
	// �� ��������� � �� ���������
	// ������ ��������� (��� �� �����������)
	const vec3 operator * (const vec3& v) {
		// ������ ��������� ����� �������� �������, ������� ��������� �� ������ ������,
		// � ���������� �� ��� ���������
		return vec3(*this) *= v; 
	}

	// ���������� []
	float& operator [] (int i) {
		// ������ �� ������� ������ ������������� ��� ������ �� ������� �������
		// ������� �������� ���� float, ����� ���� ���������� � ��� i-�� ��������
		return ((float*)this)[i];
	}
};
