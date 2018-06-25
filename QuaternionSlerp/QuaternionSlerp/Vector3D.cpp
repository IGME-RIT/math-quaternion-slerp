/*
Title: Vector Mathematics
File Name: Vector3D.cpp
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
#include "Vector3D.h"

Vector3D::Vector3D()
	: x(0), y(0), z(0)
{
}

Vector3D::Vector3D(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3D operator-(Vector3D v)
{
	return Vector3D(-v.x, -v.y, -v.z);
}

Vector3D operator+(Vector3D l, Vector3D r)
{
	return Vector3D(l.x + r.x, l.y + r.y, l.z + r.z);
}

Vector3D operator-(Vector3D l, Vector3D r)
{
	return l + (-r);
}

Vector3D operator*(float s, Vector3D v)
{
	return Vector3D(s * v.x, s * v.y, s * v.z);
}

Vector3D operator*(Vector3D v, float s)
{
	return s * v;
}

Vector3D operator/(Vector3D v, float s)
{
	return (1.0f / s) * v;
}

bool operator==(Vector3D l, Vector3D r)
{
	return ((l.x == r.x) && (l.y == r.y) && (l.z == r.z));
}

bool operator!=(Vector3D l, Vector3D r)
{
	return !(l == r);
}

float Dot(Vector3D l, Vector3D r)
{
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

Vector3D Project(Vector3D a, Vector3D b)
{
	return (Dot(a, b) / Dot(b, b)) * b;
}

Vector3D Reject(Vector3D a, Vector3D b)
{
	return a - Project(a, b);
}

Vector3D Normalize(Vector3D v)
{
	return v / Magnitude(v);
}

Vector3D Cross(Vector3D a, Vector3D b)
{
	return Vector3D(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

float Magnitude(Vector3D v)
{
	return sqrtf(Dot(v, v));
}

float MagInverse(Vector3D v)
{
	return 1.0f / Magnitude(v);
}

float MagFastInv(Vector3D v)
{
	return FastInvSqrt(Dot(v, v));
}

float MagSquared(Vector3D v)
{
	return Dot(v, v);
}

float ScalarTriple(Vector3D a, Vector3D b, Vector3D c)
{
	return Dot(Cross(a, b), c);
}

std::ostream& operator<<(std::ostream& os, Vector3D v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
