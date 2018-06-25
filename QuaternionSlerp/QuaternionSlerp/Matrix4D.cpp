/*
Title: Matrix Mathematics
File Name: Matrix4D.cpp
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
#include "Matrix4D.h"

Matrix4D::Matrix4D()
{
	n[0][0] = 1; n[0][1] = 0; n[0][2] = 0; n[0][3] = 0;
	n[1][0] = 0; n[1][1] = 1; n[1][2] = 0; n[1][3] = 0;
	n[2][0] = 0; n[2][1] = 0; n[2][2] = 1; n[2][3] = 0;
	n[3][0] = 0; n[3][1] = 0; n[3][2] = 0; n[3][3] = 1;
}

Matrix4D::Matrix4D(float n00, float n01, float n02, float n03,
	float n10, float n11, float n12, float n13,
	float n20, float n21, float n22, float n23,
	float n30, float n31, float n32, float n33)
{
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
	n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;
}

Matrix4D::Matrix4D(Vector4D a, Vector4D b, Vector4D c, Vector4D d)
{
	n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
	n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
	n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
	n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
}

float& Matrix4D::operator()(int i, int j)
{
	return n[j][i];
}

Vector4D& Matrix4D::operator[](int j)
{
	return *(Vector4D*)n[j];
}

Vector4D Matrix4D::row(int i)
{
	return Vector4D(n[0][i], n[1][i], n[2][i], n[3][i]);
}

Vector4D& Matrix4D::col(int j)
{
	return (*this)[j];
}

Matrix4D operator-(Matrix4D m)
{
	return Matrix4D(-m[0], -m[1], -m[2], -m[3]);
}

Matrix4D operator*(float s, Matrix4D m)
{
	return Matrix4D(s*m[0], s*m[1], s*m[2], s*m[3]);
}

Matrix4D operator*(Matrix4D m, float s)
{
	return s * m;
}

Matrix4D operator/(Matrix4D m, float s)
{
	return (1.0f / s)*m;
}

Matrix4D operator+(Matrix4D l, Matrix4D r)
{
	return Matrix4D(l[0] + r[0], l[1] + r[1], l[2] + r[2], l[3] + r[3]);
}

Matrix4D operator-(Matrix4D l, Matrix4D r)
{
	return l + (-r);
}

Matrix4D operator*(Matrix4D l, Matrix4D r)
{
	return Matrix4D(Dot(l.row(0), r.col(0)), Dot(l.row(0), r.col(1)), Dot(l.row(2), r.col(0)), Dot(l.row(0), r.col(3)),
		Dot(l.row(1), r.col(0)), Dot(l.row(1), r.col(1)), Dot(l.row(1), r.col(2)), Dot(l.row(1), r.col(3)),
		Dot(l.row(2), r.col(0)), Dot(l.row(2), r.col(1)), Dot(l.row(2), r.col(2)), Dot(l.row(2), r.col(3)),
		Dot(l.row(3), r.col(0)), Dot(l.row(3), r.col(1)), Dot(l.row(3), r.col(2)), Dot(l.row(3), r.col(3)));
}

Vector4D operator*(Matrix4D m, Vector4D v)
{
	return v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3];
}

Vector4D operator*(Vector4D v, Matrix4D m)
{
	return v.x * m.row(0) + v.y * m.row(1) + v.z * m.row(2) + v.w * m.row(3);
}

bool operator==(Matrix4D l, Matrix4D r)
{
	return ((l[0] == r[0]) && (l[1] == r[1]) && (l[2] == r[2]) && (l[3] == r[3]));
}

bool operator!=(Matrix4D l, Matrix4D r)
{
	return !(l == r);
}

float Determinant(Matrix4D m)
{
	const Vector3D& a = reinterpret_cast<const Vector3D&>(m[0]);
	const Vector3D& b = reinterpret_cast<const Vector3D&>(m[1]);
	const Vector3D& c = reinterpret_cast<const Vector3D&>(m[2]);
	const Vector3D& d = reinterpret_cast<const Vector3D&>(m[3]);

	const float& x = m(3, 0);
	const float& y = m(3, 1);
	const float& z = m(3, 2);
	const float& w = m(3, 3);

	Vector3D s = Cross(a, b);
	Vector3D t = Cross(c, d);
	Vector3D u = a * y - b * x;
	Vector3D v = c * w - d * z;

	return Dot(s, v) + Dot(t, u);
}

Matrix4D Inverse(Matrix4D m)
{
	const Vector3D& a = reinterpret_cast<const Vector3D&>(m[0]);
	const Vector3D& b = reinterpret_cast<const Vector3D&>(m[1]);
	const Vector3D& c = reinterpret_cast<const Vector3D&>(m[2]);
	const Vector3D& d = reinterpret_cast<const Vector3D&>(m[3]);

	const float& x = m(3, 0);
	const float& y = m(3, 1);
	const float& z = m(3, 2);
	const float& w = m(3, 3);

	Vector3D s = Cross(a, b);
	Vector3D t = Cross(c, d);
	Vector3D u = a * y - b * x;
	Vector3D v = c * w - d * z;

	float invDet = 1.0f / (Dot(s, v) + Dot(t, u));
	s = s * invDet;
	t = t * invDet;
	u = u * invDet;
	v = v * invDet;

	Vector3D r0 = Cross(b, v) + t * y;
	Vector3D r1 = Cross(v, a) - t * x;
	Vector3D r2 = Cross(d, u) + s * w;
	Vector3D r3 = Cross(u, c) - s * z;

	return Matrix4D(r0.x, r0.y, r0.z, -Dot(b, t),
		r1.x, r1.y, r1.z, Dot(a, t),
		r2.x, r2.y, r2.z, -Dot(d, s),
		r3.x, r3.y, r3.z, Dot(c, s));
}

Matrix4D InverseAdj(Matrix4D m)
{
	return Adjugate(m) / Determinant(m);
}

Matrix3D Minor(Matrix4D m, int i, int j)
{
	const int size = 3;
	float n[size][size];
	for (int k = 0, cRow = 0; k < size; k++, cRow++)
	{
		for (int l = 0, cCol = 0; l < size; l++, cCol++)
		{
			n[k][l] = m((cRow == i) ? ++cRow : cRow, (cCol == j) ? ++cCol : cCol);
		}
	}

	return Matrix3D(n[0][0], n[0][1], n[0][2],
		n[1][0], n[1][1], n[1][2],
		n[2][0], n[2][1], n[2][2]);
}

float Cofactor(Matrix4D m, int i, int j)
{
	return ((i + j) % 2 == 0 ? 1 : -1) * Determinant(Minor(m, i, j));
}

Matrix4D CofactorMatrix(Matrix4D m)
{
	return Matrix4D(Cofactor(m, 0, 0), Cofactor(m, 0, 1), Cofactor(m, 0, 2), Cofactor(m, 0, 3),
		Cofactor(m, 1, 0), Cofactor(m, 1, 1), Cofactor(m, 1, 2), Cofactor(m, 1, 3),
		Cofactor(m, 2, 0), Cofactor(m, 2, 1), Cofactor(m, 2, 2), Cofactor(m, 2, 3),
		Cofactor(m, 3, 0), Cofactor(m, 3, 1), Cofactor(m, 3, 2), Cofactor(m, 3, 3));
}

Matrix4D Adjugate(Matrix4D m)
{
	return Transpose(CofactorMatrix(m));
}

Matrix4D Transpose(Matrix4D m)
{
	return Matrix4D(m.row(0), m.row(1), m.row(2), m.row(3));
}

Matrix4D Outer(Vector4D a, Vector4D b)
{
	return Matrix4D(a.x * b.x, a.x * b.y, a.x * b.z, a.x * b.w,
		a.y * b.x, a.y * b.y, a.y * b.z, a.y * b.w,
		a.z * b.x, a.z * b.y, a.z * b.z, a.z * b.w,
		a.w * b.x, a.w * b.y, a.w * b.z, a.w * b.w);
}

Matrix4D MakeProjection(Vector4D b)
{
	return (1 / MagSquared(b)) * Outer(b, b);
}

Matrix4D MakeRejection(Vector4D b)
{
	return Matrix4D() - MakeProjection(b);
}

std::ostream& operator<<(std::ostream& os, Matrix4D m)
{
	os << "[ " << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << ", " << m(0, 3) << " ]\n"
		"[ " << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << ", " << m(1, 3) << " ]\n"
		"[ " << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << ", " << m(2, 3) << " ]\n"
		"[ " << m(3, 0) << ", " << m(3, 1) << ", " << m(3, 2) << ", " << m(3, 3) << " ]\n";
	return os;
}
