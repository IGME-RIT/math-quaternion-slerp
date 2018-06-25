/*
Title: Matrix Mathematics
File Name: Matrix3D.h
Copyright © 2016
Author: Andrew Litfin
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "Vector3D.h"
#include "Matrix2D.h"

#include <iostream>

// A 3 by 3 matrix of floats.
struct Matrix3D
{
private:
	float n[3][3];

public:
	Matrix3D();

	Matrix3D(float n00, float n01, float n02,
		float n10, float n11, float n12,
		float n20, float n21, float n22);

	Matrix3D(Vector3D a, Vector3D b, Vector3D c);

	float& operator()(int i, int j);

	Vector3D& operator[](int j);

	Vector3D row(int i);
	Vector3D& col(int j);
};

Matrix3D operator-(Matrix3D m);
Matrix3D operator*(float s, Matrix3D m);
Matrix3D operator*(Matrix3D m, float s);
Matrix3D operator/(Matrix3D m, float s);
Matrix3D operator+(Matrix3D l, Matrix3D r);
Matrix3D operator-(Matrix3D l, Matrix3D r);
Matrix3D operator*(Matrix3D l, Matrix3D r);

Vector3D operator*(Matrix3D m, Vector3D v);
Vector3D operator*(Vector3D v, Matrix3D m);

bool operator==(Matrix3D l, Matrix3D r);
bool operator!=(Matrix3D l, Matrix3D r);

float Determinant(Matrix3D m);

Matrix3D Inverse(Matrix3D m);
Matrix3D InverseAdj(Matrix3D m);
Matrix2D Minor(Matrix3D m, int i, int j);
float Cofactor(Matrix3D m, int i, int j);
Matrix3D CofactorMatrix(Matrix3D m);
Matrix3D Adjugate(Matrix3D m);

Matrix3D Transpose(Matrix3D m);

Matrix3D Outer(Vector3D a, Vector3D b);
Matrix3D MakeProjection(Vector3D b);
Matrix3D MakeRejection(Vector3D b);

// Returns a matrix representing a counter-clockwise rotation of theta radians about the x-axis.
Matrix3D MakeRotationX(float theta);

// Returns a matrix representing a counter-clockwise rotation of theta radians about the y-axis.
Matrix3D MakeRotationY(float theta);

// Returns a matrix representing a counter-clockwise rotation of theta radians about the z-axis.
Matrix3D MakeRotationZ(float theta);

// Returns a matrix representing a counter-clockwise rotation of theta radians about the vector v using Rodrigues' Formula.
Matrix3D MakeRotation(float theta, Vector3D v);

// Similar to MakeProjection and MakeRejection, CrossMat returns a matrix representing the "left cross product" by vector a.
// That is, given two 3D vectors a and b, CrossMat(a) * b = Cross(a, b)
Matrix3D CrossMat(Vector3D a);

std::ostream& operator<<(std::ostream& os, Matrix3D m);
