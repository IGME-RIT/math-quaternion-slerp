/*
Title: Vector Mathematics
File Name: Vector3D.h
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

#include <iostream>
#include <math.h>

#include "helpers.h"

struct Vector3D
{
	float x, y, z;

	Vector3D();
	Vector3D(float x, float y, float z);
};

Vector3D operator-(Vector3D v);

Vector3D operator+(Vector3D l, Vector3D r);
Vector3D operator-(Vector3D l, Vector3D r);

Vector3D operator*(float s, Vector3D v);
Vector3D operator*(Vector3D v, float s);
Vector3D operator/(Vector3D v, float s);

bool operator==(Vector3D l, Vector3D r);
bool operator!=(Vector3D l, Vector3D r);

float Dot(Vector3D l, Vector3D r);

Vector3D Project(Vector3D a, Vector3D b);
Vector3D Reject(Vector3D a, Vector3D b);

Vector3D Normalize(Vector3D v);

// Calculates the cross product of a and b according to the right-hand rule.
Vector3D Cross(Vector3D a, Vector3D b);

float Magnitude(Vector3D v);
float MagInverse(Vector3D v);
float MagFastInv(Vector3D v);
float MagSquared(Vector3D v);

// Calculates the volume of the parallelepiped defined by a, b, and c.
float ScalarTriple(Vector3D a, Vector3D b, Vector3D c);

std::ostream& operator<<(std::ostream& os, Vector3D v);
