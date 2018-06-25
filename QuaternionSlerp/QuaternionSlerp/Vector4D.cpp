/*
Title: Vector Mathematics
File Name: Vector4D.cpp
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
#include "Vector4D.h"

Vector4D::Vector4D()
	: x(0), y(0), z(0), w(0)
{
}

Vector4D::Vector4D(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

Vector4D::Vector4D(Vector3D v, float w)
	: x(v.x), y(v.y), z(v.z), w(w)
{
}

Vector4D operator-(Vector4D v)
{
	return Vector4D(-v.x, -v.y, -v.z, -v.w);
}

Vector4D operator+(Vector4D l, Vector4D r)
{
	return Vector4D(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

Vector4D operator-(Vector4D l, Vector4D r)
{
	return l + (-r);
}

Vector4D operator*(float s, Vector4D v)
{
	return Vector4D(s * v.x, s * v.y, s * v.z, s * v.w);
}

Vector4D operator*(Vector4D v, float s)
{
	return s * v;
}

Vector4D operator/(Vector4D v, float s)
{
	return (1.0f / s) * v;
}

bool operator==(Vector4D l, Vector4D r)
{
	return ((l.x == r.x) && (l.y == r.y) && (l.z == r.z) && (l.w == r.w));
}

bool operator!=(Vector4D l, Vector4D r)
{
	return !(l == r);
}

float Dot(Vector4D l, Vector4D r)
{
	return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
}

Vector4D Project(Vector4D a, Vector4D b)
{
	return (Dot(a, b) / Dot(b, b)) * b;
}

Vector4D Reject(Vector4D a, Vector4D b)
{
	return a - Project(a, b);
}

Vector4D Normalize(Vector4D v)
{
	return v / Magnitude(v);
}

Vector4D Pointify(Vector4D v)
{
	return (v.w == 0) ? v + Vector4D(0, 0, 0, 1) : v / v.w;
}

float Magnitude(Vector4D v)
{
	return sqrtf(Dot(v, v));
}

float MagInverse(Vector4D v)
{
	return 1.0f / Magnitude(v);
}

float MagFastInv(Vector4D v)
{
	return FastInvSqrt(Dot(v, v));
}

float MagSquared(Vector4D v)
{
	return Dot(v, v);
}

std::ostream & operator<<(std::ostream& os, Vector4D v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}
