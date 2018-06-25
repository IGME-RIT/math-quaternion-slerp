/*
Title: Matrix Mathematics
File Name: Matrix3D.cpp
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
#include "Matrix3D.h"

Matrix3D::Matrix3D()
{
	n[0][0] = 1; n[0][1] = 0; n[0][2] = 0;
	n[1][0] = 0; n[1][1] = 1; n[1][2] = 0;
	n[2][0] = 0; n[2][1] = 0; n[2][2] = 1;
}

Matrix3D::Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22)
{
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
}

Matrix3D::Matrix3D(Vector3D a, Vector3D b, Vector3D c)
{
	n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
	n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
	n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
}

float& Matrix3D::operator()(int i, int j)
{
	return n[j][i];
}

Vector3D& Matrix3D::operator[](int j)
{
	return *(Vector3D*)n[j];
}

Vector3D Matrix3D::row(int i)
{
	return Vector3D(n[0][i], n[1][i], n[2][i]);
}

Vector3D& Matrix3D::col(int j)
{
	return (*this)[j];
}

Matrix3D operator-(Matrix3D m)
{
	return Matrix3D(-m[0], -m[1], -m[2]);
}

Matrix3D operator*(float s, Matrix3D m)
{
	return Matrix3D(s*m[0], s*m[1], s*m[2]);
}

Matrix3D operator*(Matrix3D m, float s)
{
	return s * m;
}

Matrix3D operator/(Matrix3D m, float s)
{
	return (1.0f / s)*m;
}

Matrix3D operator+(Matrix3D l, Matrix3D r)
{
	return Matrix3D(l[0] + r[0], l[1] + r[1], l[2] + r[2]);
}

Matrix3D operator-(Matrix3D l, Matrix3D r)
{
	return l + (-r);
}

Matrix3D operator*(Matrix3D l, Matrix3D r)
{
	return Matrix3D(Dot(l.row(0), r.col(0)), Dot(l.row(0), r.col(1)), Dot(l.row(0), r.col(2)),
		Dot(l.row(1), r.col(0)), Dot(l.row(1), r.col(1)), Dot(l.row(1), r.col(2)),
		Dot(l.row(2), r.col(0)), Dot(l.row(2), r.col(1)), Dot(l.row(2), r.col(2)));
}

Vector3D operator*(Matrix3D m, Vector3D v)
{
	return v.x * m[0] + v.y * m[1] + v.z * m[2];
}

Vector3D operator*(Vector3D v, Matrix3D m)
{
	return v.x * m.row(0) + v.y * m.row(1) + v.z * m.row(2);
}

bool operator==(Matrix3D l, Matrix3D r)
{
	return ((l[0] == r[0]) && (l[1] == r[1]) && (l[2] == r[2]));
}

bool operator!=(Matrix3D l, Matrix3D r)
{
	return !(l == r);
}

float Determinant(Matrix3D m)
{
	return m(0, 0) * m(1, 1) * m(2, 2) + m(0, 1) * m(1, 2) * m(2, 0) + m(0, 2) * m(1, 0) * m(2, 1)
		- (m(0, 0) * m(1, 2) * m(2, 1) + m(0, 1) * m(1, 0) * m(2, 2) + m(0, 2) * m(1, 1) * m(2, 0));
}

Matrix3D Inverse(Matrix3D m)
{
	const Vector3D& a = m[0];
	const Vector3D& b = m[1];
	const Vector3D& c = m[2];

	Vector3D r0 = Cross(b, c);
	Vector3D r1 = Cross(c, a);
	Vector3D r2 = Cross(a, b);

	float invDet = 1.0f / Dot(r2, c);

	return Matrix3D(r0.x * invDet, r0.y * invDet, r0.z * invDet,
		r1.x * invDet, r1.y * invDet, r1.z * invDet,
		r2.x * invDet, r2.y * invDet, r2.z * invDet);
}

Matrix3D InverseAdj(Matrix3D m)
{
	return Adjugate(m) / Determinant(m);
}

Matrix2D Minor(Matrix3D m, int i, int j)
{
	const int size = 2;
	float n[size][size];
	for (int k = 0, cRow = 0; k < size; k++, cRow++)
	{
		for (int l = 0, cCol = 0; l < size; l++, cCol++)
		{
			n[k][l] = m((cRow == i) ? ++cRow : cRow, (cCol == j) ? ++cCol : cCol);
		}
	}

	return Matrix2D(n[0][0], n[0][1], n[1][0], n[1][1]);
}

float Cofactor(Matrix3D m, int i, int j)
{
	return ((i + j) % 2 == 0 ? 1 : -1) * Determinant(Minor(m, i, j));
}

Matrix3D CofactorMatrix(Matrix3D m)
{
	return Matrix3D(Cofactor(m, 0, 0), Cofactor(m, 0, 1), Cofactor(m, 0, 2),
		Cofactor(m, 1, 0), Cofactor(m, 1, 1), Cofactor(m, 1, 2),
		Cofactor(m, 2, 0), Cofactor(m, 2, 1), Cofactor(m, 2, 2));
}

Matrix3D Adjugate(Matrix3D m)
{
	return Transpose(CofactorMatrix(m));
}

Matrix3D Transpose(Matrix3D m)
{
	return Matrix3D(m.row(0), m.row(1), m.row(2));
}

Matrix3D Outer(Vector3D a, Vector3D b)
{
	return Matrix3D(a.x * b.x, a.x * b.y, a.x * b.z,
		a.y * b.x, a.y * b.y, a.y * b.z,
		a.z * b.x, a.z * b.y, a.z * b.z);
}

Matrix3D MakeProjection(Vector3D b)
{
	return (1 / MagSquared(b)) * Outer(b, b);
}

Matrix3D MakeRejection(Vector3D b)
{
	return Matrix3D() - MakeProjection(b);
}

Matrix3D MakeRotationX(float theta)
{
	float c = cosf(theta);
	float s = sinf(theta);

	return Matrix3D(1, 0, 0,
		0, c, -s,
		0, s, c);
}

Matrix3D MakeRotationY(float theta)
{
	float c = cosf(theta);
	float s = sinf(theta);

	return Matrix3D(c, 0, s,
		0, 1, 0,
		-s, 0, c);
}

Matrix3D MakeRotationZ(float theta)
{
	float c = cosf(theta);
	float s = sinf(theta);

	return Matrix3D(c, -s, 0,
		s, c, 0,
		0, 0, 1);
}

Matrix3D MakeRotation(float theta, Vector3D v)
{
	v = v * MagInverse(v);
	float c = cosf(theta);
	float s = sinf(theta);

	// This is one possible statement of Rodrigues' Rotation formula
	return c * Matrix3D() + (1 - c) * Outer(v, v) + s * CrossMat(v);
}

Matrix3D CrossMat(Vector3D a)
{
	return Matrix3D(0, -a.z, a.y,
		a.z, 0, -a.x,
		-a.y, a.x, 0);
}

std::ostream& operator<<(std::ostream& os, Matrix3D m)
{
	os << "[ " << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << " ]\n"
		"[ " << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << " ]\n"
		"[ " << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << " ]\n";
	return os;
}
