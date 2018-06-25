/*
Title: Matrix Mathematics
File Name: Matrix4D.h
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

#include "Vector4D.h"
#include "Matrix3D.h"

#include <iostream>

struct Matrix4D
{
private:
	float n[4][4];

public:
	Matrix4D();

	Matrix4D(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23,
		float n30, float n31, float n32, float n33);

	Matrix4D(Vector4D a, Vector4D b, Vector4D c, Vector4D d);

	float& operator()(int i, int j);

	Vector4D& operator[](int j);

	Vector4D row(int i);
	Vector4D& col(int j);
};

Matrix4D operator-(Matrix4D m);
Matrix4D operator*(float s, Matrix4D m);
Matrix4D operator*(Matrix4D m, float s);
Matrix4D operator/(Matrix4D m, float s);
Matrix4D operator+(Matrix4D l, Matrix4D r);
Matrix4D operator-(Matrix4D l, Matrix4D r);
Matrix4D operator*(Matrix4D l, Matrix4D r);

Vector4D operator*(Matrix4D m, Vector4D v);
Vector4D operator*(Vector4D v, Matrix4D m);

bool operator==(Matrix4D l, Matrix4D r);
bool operator!=(Matrix4D l, Matrix4D r);

float Determinant(Matrix4D m);

Matrix4D Inverse(Matrix4D m);
Matrix4D InverseAdj(Matrix4D m);
Matrix3D Minor(Matrix4D m, int i, int j);
float Cofactor(Matrix4D m, int i, int j);
Matrix4D CofactorMatrix(Matrix4D m);
Matrix4D Adjugate(Matrix4D m);

Matrix4D Transpose(Matrix4D m);

Matrix4D Outer(Vector4D a, Vector4D b);
Matrix4D MakeProjection(Vector4D b);
Matrix4D MakeRejection(Vector4D b);

std::ostream& operator<<(std::ostream& os, Matrix4D m);
