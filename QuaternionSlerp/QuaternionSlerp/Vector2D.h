/*
Title: Vector Mathematics
File Name: Vector2D.h
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

struct Vector2D
{
	float x, y;

	Vector2D();

	Vector2D(float x, float y);
};

Vector2D operator-(Vector2D v);
Vector2D operator+(Vector2D l, Vector2D r);
Vector2D operator-(Vector2D l, Vector2D r);
Vector2D operator*(float s, Vector2D v);
Vector2D operator*(Vector2D v, float s);
Vector2D operator/(Vector2D v, float s);

bool operator==(Vector2D l, Vector2D r);
bool operator!=(Vector2D l, Vector2D r);

float Dot(Vector2D l, Vector2D r);
Vector2D Project(Vector2D a, Vector2D b);
Vector2D Reject(Vector2D a, Vector2D b);

Vector2D Normalize(Vector2D v);

float Magnitude(Vector2D v);
float MagInverse(Vector2D v);
float MagFastInv(Vector2D v);
float MagSquared(Vector2D v);

std::ostream& operator<<(std::ostream& os, Vector2D v);
