#pragma once

#include <iostream>
#include <math.h>
#include "Vector3D.h"
#include "Matrix4D.h"

struct Quaternion
{
	float w, x, y, z;

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float w, Vector3D v);
};

Quaternion operator+(Quaternion q, Quaternion r);
Quaternion operator-(Quaternion q);
Quaternion operator-(Quaternion q, Quaternion r);

Quaternion operator*(Quaternion q, Quaternion r);
Quaternion operator*(float s, Quaternion q);
Quaternion operator*(Quaternion q, float s);

float Norm(Quaternion q);
float Magnitude(Quaternion q);

Quaternion operator/(Quaternion q, float s);
Quaternion operator/(Quaternion q, Quaternion r);

Quaternion Normalize(Quaternion q);
Quaternion Conjugate(Quaternion q);
Quaternion Inverse(Quaternion q);

float Dot(Quaternion q, Quaternion r);
float AngleBetweenQuaternions(Quaternion q, Quaternion r);

Quaternion Rotation(Vector3D v, float a);
Quaternion Slerp(Quaternion a, Quaternion b, double t);

Matrix3D RotationMatrix(Quaternion q);

Vector3D RotateVector(Vector3D v, Quaternion q);

std::ostream& operator<<(std::ostream& os, Quaternion q);