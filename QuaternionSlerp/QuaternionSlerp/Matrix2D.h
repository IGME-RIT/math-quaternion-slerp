/*
Title: Matrix Mathematics
File Name: Matrix2D.h
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

#include "Vector2D.h"

#include <iostream>
#include <cmath>

// A 2x2 matrix of floats.
struct Matrix2D
{
private:
	// Our 4 values in a 2-by-2 grid.
	float n[2][2];
	// N.B. that we have chosen to hold these values in column-major order,
	//   which is why this is private (or else it is very easy to reverse the row-column order when reading).
	// By column-major, we mean that as memory increases linearly, the matrix is actually read down columns first, then rows.
	// So for example the linear memory would look something like this:
	//   -----+---------------------------------------+-----
	//    ... | n[0][0] | n[0][1] | n[1][0] | n[1][1] | ...
	//   -----+---------------------------------------+-----
	// While actually representing the matrix
	//   [ n[0][0] n[1][0] ]
	//   [ n[0][1] n[1][1] ]
	// (Even though by convention in mathematical literature, when referencing a matrix element, we say the row first, then the column.)

public:
	// The default constructor returns the Identity matrix (1s along the diagonal, 0s everywhere else)
	Matrix2D();
	// We have chosen the multiplicative identity instead of the additive identity because matrix addition is used less commonly than multiplication.

	// Sets the nij-th element of the matrix
	Matrix2D(float n00, float n01,
		float n10, float n11);

	// Sets the first column to a and the second to b
	Matrix2D(Vector2D a, Vector2D b);

	// Returns a reference to nij (i.e., the element at row i, column j)
	float& operator()(int i, int j);

	// Returns a reference to column j
	Vector2D& operator[](int j);

	// Returns a new Vector2D that is row i
	Vector2D row(int i);
	// Note that we cannot return a reference because row values are not neighbors in memory,
	//  so we must copy the values

	// Returns a reference to column j (alias for [])
	Vector2D& col(int j);
};

// Negates the matrix m
Matrix2D operator-(Matrix2D m);

// Uniformly scales all elements of m by s and returns the new matrix
Matrix2D operator*(float s, Matrix2D m);

// Alias for s * m (scalar multiplication is commutative)
Matrix2D operator*(Matrix2D m, float s);

// Divides each element of m by s
Matrix2D operator/(Matrix2D m, float s);

// Returns the matrix sum of l and r. This operation will not be commonly used.
// This operation is commutative.
Matrix2D operator+(Matrix2D l, Matrix2D r);

// Subracts matrix r from matrix l.
Matrix2D operator-(Matrix2D l, Matrix2D r);

// Returns the matrix product of l and r.
// This operation is NOT commutative!
Matrix2D operator*(Matrix2D l, Matrix2D r);

// Returns the product of m and v (as a column vector).
Vector2D operator*(Matrix2D m, Vector2D v);

// Returns the product of v (as a row vector) and m.
Vector2D operator*(Vector2D v, Matrix2D m);

// Compares l and r. Returns true if l and r are equal.
bool operator==(Matrix2D l, Matrix2D r);

// Negation of ==
bool operator!=(Matrix2D l, Matrix2D r);

// Returns the determinant of m (the area of the parallelogram with sides m[0] and m[1]).
float Determinant(Matrix2D m);

// Returns the inverse of m.
// The inverse of a matrix is the unique matrix such that Inverse(m) * m = m * Inverse(m) = I,
//  where I is the identity matrix.
Matrix2D Inverse(Matrix2D m);

// Returns the inverse of m, calculated slightly differently.
Matrix2D InverseAdj(Matrix2D m);
// For 2x2 matrices, Inverse and InverseAdj are roughly the same speed (based on experimental testing).

// The minor of a matrix at row i, column j, is an (n-1) by (n-1) matrix that excludes row i and column j.
float Minor(Matrix2D m, int i, int j);
// Note that the minor has the same order as the original matrix (i.e., the rows and columns are not permuted in any way,
//  which is why we cannot use modular arithmetic to calculate minors).

// The Cofactor of m at row i, column j, is the Determinant of Minor(m, i, j) times -1 if i + j is odd or 1 if i + j is even.
float Cofactor(Matrix2D m, int i, int j);

// The Cofactor Matrix C of a matrix m is an n by n matrix where each element C(i, j) is the Cofactor of m at (i, j)
Matrix2D CofactorMatrix(Matrix2D m);

// The Adjugate of m is simply the transpose of the Cofactor Matrix.
// It has the unique property that adj(m) = det(m)*Inverse(m)
Matrix2D Adjugate(Matrix2D m);

// The Transpose of a matrix m, mT, is the matrix achieved by swapping off-diagonal elements.
// Formally, Transpose(m)(i,j) = m(j, i)
Matrix2D Transpose(Matrix2D m);

// The Outer product of two vectors is equivalent to the matrix product of a (as a column vector) and b (as a row vector).
// If a is an n-dimensional vector and b is an m-dimensional vector, then a * b is an nx1 matrix times a 1xm matrix,
// so the result is an nxm matrix.
// Alternatively, if a and b are both considered as column vectors, then Outer(a, b) = a * Transpose(b)
Matrix2D Outer(Vector2D a, Vector2D b);

// Returns the outer product of b with itself, divided by the magnitude of b squared.
// Equivalently, the outer product of Normalize(b) with itself.
// This is useful if you need to project a large number of vectors onto one particular vector, for example with the Graham-Shmidt process,
//  as the projection matrix can only be calculated once then re-used.
// Note that for only one projection, this is actually less efficient.
// Usage: Given two vectors a, and b, Project(a, b) = MakeProjection(b) * a
Matrix2D MakeProjection(Vector2D b);

// Returns the identity minus MakeProjection(b).
// Useful to reject many vectors from one.
// Similar to MakeProjection, Reject(a, b) = MakeRejection(b) * a
Matrix2D MakeRejection(Vector2D b);

// Returns the 2D rotation matrix corresponding to a counter-clockwise rotation by theta radians.
Matrix2D MakeRotation(float theta);

// Returns a 2D matrix that is the reflection of the provided matrix (along x-axis, y-axis, origin, line x = y)
Matrix2D ReflectMatrix(Matrix2D m, Matrix2D reflectionMatrix);

// A simple << operator for use with std::cout.
// Note that it ends with a newline.
std::ostream& operator<<(std::ostream& os, Matrix2D m);
