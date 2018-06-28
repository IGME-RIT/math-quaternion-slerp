/*
Title: Quaternion Math
File Name: Quaternion.h
Author: Parth Contractor
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

#include <iostream>
#include <math.h>
#include "Matrix3D.h"
#include "Vector3D.h"

struct Quaternion
{
	float w, x, y, z;

	Quaternion();
	Quaternion(float w, float x, float y, float z);

	// This constructor use 'injects' a Vector3D into the imaginary part of the Quaternion (i.e. x, y, z values)
	Quaternion(float w, Vector3D v);
};

// Gives the sum of two quaternions
Quaternion operator+(Quaternion q, Quaternion r);
// Negates the quaternion
Quaternion operator-(Quaternion q);
// Gives the difference between two quaternions
Quaternion operator-(Quaternion q, Quaternion r);

// Multiplies two Quaternions
Quaternion operator*(Quaternion q, Quaternion r);
// Multiplies a scalar number with the Quaternion
Quaternion operator*(float s, Quaternion q);
Quaternion operator*(Quaternion q, float s);

// Gives the norm of the Quaternion
float Norm(Quaternion q);
// Gives the magnitude of the Quaternion
float Magnitude(Quaternion q);

// Divides the Quaternion by a scalar
Quaternion operator/(Quaternion q, float s);
// Divides one Quaternion by another
Quaternion operator/(Quaternion q, Quaternion r);

// Returns a normalized quaternion
Quaternion Normalize(Quaternion q);
// Returns a Quaternion which is a conjugate of the given Quaternion
Quaternion Conjugate(Quaternion q);
// Returns a Quaternion that is the inverse of the given Quaternion
Quaternion Inverse(Quaternion q);

// Calculate the Dot product of two Quaternion
float Dot(Quaternion q, Quaternion r);
// Calculate the angle between two Quaternion
float AngleBetweenQuaternions(Quaternion q, Quaternion r);

// Returns a quaternion for the rotation by the angle provided and vector as the axis around which to rotate
Quaternion Rotation(Vector3D v, float a);
// SLERP(Spherical linear interpolation) moves a point from one position to another over time
Quaternion Slerp(Quaternion a, Quaternion b, double t);

// Returns a Matrix3D used for rotation
Matrix3D RotationMatrix(Quaternion q);

// Returns rotated vector along the given quaternion
Vector3D RotateVector(Vector3D v, Quaternion q);

std::ostream& operator<<(std::ostream& os, Quaternion q);