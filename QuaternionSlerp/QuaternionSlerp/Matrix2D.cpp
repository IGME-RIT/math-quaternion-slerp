/*
Title: Matrix Mathematics
File Name: Matrix2D.cpp
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
#include "Matrix2D.h"

Matrix2D::Matrix2D()
{
	// The default constructor gives the identity matrix.
	// 1s on the diagonal, 0s everywhere else.
	n[0][0] = 1; n[0][1] = 0;
	n[1][0] = 0; n[1][1] = 1;
}

Matrix2D::Matrix2D(float n00, float n01, float n10, float n11)
{
	// Remember, we store the elements internally in column-major,
	// but still treat everything as if it were row-major.
	// That's why n[j][i] stores element nij
	n[0][0] = n00; n[0][1] = n10;
	n[1][0] = n01; n[1][1] = n11;
}

Matrix2D::Matrix2D(Vector2D a, Vector2D b)
{
	// For the same reason as the above constructor, we must "reverse" what we'd think is the order.
	n[0][0] = a.x; n[0][1] = a.y;
	n[1][0] = b.x; n[1][1] = b.y;
}

float& Matrix2D::operator()(int i, int j)
{
	// As a result of storing the matrix column-major, the (i, j) element of the matrix is actually n[j][i].
	// This is why n has the `private' access modifier and instead we have overloaded operator().
	return n[j][i];
}

Vector2D& Matrix2D::operator[](int j)
{
	// Operations like this are why we choose to store in column-major.
	// When treating vectors as column vectors, as we often do in games,
	//  it is useful to be able to access the columns of a matrix,
	//  as you will see in operator*(Matrix, Vector)
	return *(Vector2D*)n[j];
}

Vector2D Matrix2D::row(int i)
{
	// As stated in the header, the elements of the rows do not occupy continuous memory, so we must copy it to a new location.
	return Vector2D(n[0][i], n[1][i]);
}

Vector2D& Matrix2D::col(int j)
{
	// Dereference this, then `call' the [] function.
	return (*this)[j];
}

Matrix2D operator-(Matrix2D m)
{
	// Here and for every operator defined on matrices, we can utilize the fact that
	//  many of the operations we are defining are extremely similar to operations we have already defined.
	// Where have we already defined them? For Vectors.
	return Matrix2D(-m[0], -m[1]);
}

Matrix2D operator*(float s, Matrix2D m)
{
	return Matrix2D(s * m[0], s * m[1]);
}

Matrix2D operator*(Matrix2D m, float s)
{
	return s * m;
}

Matrix2D operator/(Matrix2D m, float s)
{
	return (1.0f / s)*m;
}

Matrix2D operator+(Matrix2D l, Matrix2D r)
{
	return Matrix2D(l[0] + r[0], l[1] + r[1]);
}

Matrix2D operator-(Matrix2D l, Matrix2D r)
{
	return l + (-r);
}

Matrix2D operator*(Matrix2D l, Matrix2D r)
{
	// Matrix multiplication can be computed as the dot product of rows into columns.
	// In production code you would want to expand this, especially since this is just a 2D matrix,
	//  but I have chosen mathematical meaning over speedy code.
	return Matrix2D(Dot(l.row(0), r.col(0)), Dot(l.row(0), r.col(1)),
		Dot(l.row(1), r.col(0)), Dot(l.row(1), r.col(1)));
}

Vector2D operator*(Matrix2D m, Vector2D v)
{
	// The product of a matrix with a column vector is a linear combination of the columns of the matrix.
	return v.x * m[0] + v.y * m[1];
}

Vector2D operator*(Vector2D v, Matrix2D m)
{
	// The product of a row vector with a matrix is a linear combination of the rows of the matrix.
	return v.x * m.row(0) + v.y * m.row(1);
}

bool operator==(Matrix2D l, Matrix2D r)
{
	return ((l[0] == r[0]) && (l[1] == r[1]));
}

bool operator!=(Matrix2D l, Matrix2D r)
{
	return !(l == r);
}

float Determinant(Matrix2D m)
{
	return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
}

Matrix2D Inverse(Matrix2D m)
{
	float invDet = 1.0f / Determinant(m);
	return Matrix2D(m(1, 1) * invDet, -m(0, 1) * invDet, -m(1, 0) * invDet, m(0, 0) * invDet);
}

Matrix2D InverseAdj(Matrix2D m)
{
	return Adjugate(m) / Determinant(m);
}

float Minor(Matrix2D m, int i, int j)
{
	// We can use arithmetic mod 2 to just choose the other corner of the matrix than the one given by i and j.
	return m((i + 1) % 2, (j + 1) % 2);
}

float Cofactor(Matrix2D m, int i, int j)
{
	return ((i + j) % 2 == 0 ? 1 : -1) * Minor(m, i, j);
}

Matrix2D CofactorMatrix(Matrix2D m)
{
	return Matrix2D(Cofactor(m, 0, 0), Cofactor(m, 0, 1),
		Cofactor(m, 1, 0), Cofactor(m, 1, 1));
}

Matrix2D Adjugate(Matrix2D m)
{
	return Transpose(CofactorMatrix(m));
}

Matrix2D Transpose(Matrix2D m)
{
	// As with the row operation, Transpose must return a copy of the given matrix, instead of a reference to the original.
	return Matrix2D(m.row(0), m.row(1));
}

Matrix2D Outer(Vector2D a, Vector2D b)
{
	return Matrix2D(a.x * b.x, a.x * b.y,
		a.y * b.x, a.y * b.y);
}

Matrix2D MakeProjection(Vector2D b)
{
	// To prove this is correct, consider the Project(a, b) function, which projects a onto b.
	// It returns (Dot(a, b) / Dot(b, b)) * b.
	// Now that we have matrix multiplication, we can regard this more simply as
	//  = 1/|b|^2 * Dot(b, a) * b, since the dot product is commutative
	//  = 1/|b|^2 * b * Dot(b, a), since scalar multiplication is commutative
	//  = 1/|b|^2 * b * (Transpose(b) * a), where a and b are considered as column vectors, so bT * a will return a "1x1 matrix", ie a scalar
	//  = 1/|b|^2 * (b * Transpose(b)) * a, since matrix multiplication is associative
	//  = (1/|b|^2 * Outer(b, b)) * a, by definition of the outer product
	return (1 / MagSquared(b)) * Outer(b, b);
}

Matrix2D MakeRejection(Vector2D b)
{
	// Again, as proof of correctness,
	// Reject(a, b) = a - Project(a, b)
	//  = I*a - MakeProjection(b)*a, where I is the Identity matrix (1s along the diagonal and 0s everywhere else)
	//  = (I - MakeProjection(b))*a
	return Matrix2D() - MakeProjection(b);
}

Matrix2D MakeRotation(float theta)
{
	// To construct the matrix, we can consider the image of the standard basis unit vectors under the matrix.
	// (We can do this since the result of a matrix-vector multiplication is a linear combination of the columns of the matrix.)
	// Then, using the unit circle, we can determine that for a rotation by angle theta, M(theta),
	//  we should have that M(theta)*(1, 0) = (cos(theta), sin(theta)), and
	//  M(theta)*(0, 1) = (-sin(theta), cos(theta)).
	// We simply then set the columns of the matrix equal to these vectors, and voila.
	return Matrix2D(cosf(theta), -sinf(theta),
		sinf(theta), cosf(theta));
}

Matrix2D ReflectMatrix(Matrix2D m, Matrix2D reflectionMatrix)
{
	// When we want to create a reflection image we multiply the vertex matrix of the our figure with what is called a relfection matrix.
	// The most common reflection matrices are:

	// For reflection on X-Axis:
	// [1  0]
	// [0 -1]

	// For reflection on Y-Axis:
	// [-1 0]
	// [0  1]

	// For reflection in the origin:
	// [-1 0]
	// [0 -1]

	// For reflection in the line y = x:
	// [0 1]
	// [1 0]
	return m * reflectionMatrix;
}


std::ostream& operator<<(std::ostream& os, Matrix2D m)
{
	os << "[ " << m(0, 0) << " " << m(0, 1) << " ]\n"
		"[ " << m(1, 0) << " " << m(1, 1) << " ]\n";
	return os;
}
