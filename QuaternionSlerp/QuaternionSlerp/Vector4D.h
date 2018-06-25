/*
Title: Vector Mathematics
File Name: Vector4D.h
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
#include "Vector3D.h"

struct Vector4D
{
	float x, y, z, w;

	Vector4D();
	Vector4D(float x, float y, float z, float w);

	// This is a new constructor that is able to `inject' a 3D vector into 4D space.
	Vector4D(Vector3D v, float w);
};

Vector4D operator-(Vector4D v);

Vector4D operator+(Vector4D l, Vector4D r);
Vector4D operator-(Vector4D l, Vector4D r);

Vector4D operator*(float s, Vector4D v);
Vector4D operator*(Vector4D v, float s);
Vector4D operator/(Vector4D v, float s);

bool operator==(Vector4D l, Vector4D r);
bool operator!=(Vector4D l, Vector4D r);

float Dot(Vector4D l, Vector4D r);

Vector4D Project(Vector4D a, Vector4D b);
Vector4D Reject(Vector4D a, Vector4D b);

Vector4D Normalize(Vector4D v);

// Divides v by its w component or adds 1 to the w component, such that the final w component is 1.
// In this way, it becomes a homogeneous point.
Vector4D Pointify(Vector4D v);

float Magnitude(Vector4D v);
float MagInverse(Vector4D v);
float MagFastInv(Vector4D v);
float MagSquared(Vector4D v);

std::ostream& operator<<(std::ostream& os, Vector4D v);
