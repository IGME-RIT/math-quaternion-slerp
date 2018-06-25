/*
Title: Vector Mathematics
File Name: Vector2D.cpp
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
#include "Vector2D.h"

Vector2D::Vector2D()
	: x(0), y(0)
{
}

Vector2D::Vector2D(float x, float y)
	: x(x), y(y)
{
}

Vector2D operator-(Vector2D v)
{
	return Vector2D(-v.x, -v.y);
}

Vector2D operator+(Vector2D l, Vector2D r)
{
	return Vector2D(l.x + r.x, l.y + r.y);
}

Vector2D operator-(Vector2D l, Vector2D r)
{
	return l + (-r);
}

Vector2D operator*(float s, Vector2D v)
{
	return Vector2D(s * v.x, s * v.y);
}

Vector2D operator*(Vector2D v, float s)
{
	return s * v;
}

Vector2D operator/(Vector2D v, float s)
{
	return (1.0f / s) * v;
}

bool operator==(Vector2D l, Vector2D r)
{
	return ((l.x == r.x) && (l.y == r.y));
}

bool operator!=(Vector2D l, Vector2D r)
{
	return !(l == r);
}

float Dot(Vector2D l, Vector2D r)
{
	return l.x * r.x + l.y * r.y;
}

Vector2D Project(Vector2D a, Vector2D b)
{
	return  (Dot(a, b) / Dot(b, b)) * b;
}

Vector2D Reject(Vector2D a, Vector2D b)
{
	return a - Project(a, b);
}

Vector2D Normalize(Vector2D v)
{
	return v / Magnitude(v);
}

float Magnitude(Vector2D v)
{
	return sqrtf(Dot(v, v));
}

float MagInverse(Vector2D v)
{
	return 1.0f / Magnitude(v);
}

float MagFastInv(Vector2D v)
{
	return FastInvSqrt(Dot(v, v));
}

float MagSquared(Vector2D v)
{
	return Dot(v, v);
}

std::ostream& operator<<(std::ostream& os, Vector2D v)
{
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}
