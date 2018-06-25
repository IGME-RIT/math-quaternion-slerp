/*
Title: Vector Mathematics
File Name: helpers.cpp
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
#include "helpers.h"

float FastInvSqrt(float x)
{
	// Code taken from Quake III Arena, public domain

	// This code is a great bit of history and trivia in the games industry.
	// It was originally attributed to John Carmack and id Software, but it apparently goes further back than that.

	// This is a great example of how black-majick-y C++ can get.
	// See [the Wikipedia article](https://en.wikipedia.org/wiki/Fast_inverse_square_root) for an explanation.

	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = x * 0.5F;
	y = x;
	i = *(long *)&y;						// evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);				// what
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));	// 1st iteration
											//	y = y * (threehalfs - (x2 * y * y));	// 2nd iteration, this can be removed

	return y;
}

// Returns a random real number in the interval [min, max] (inclusive on both ends)
float randFloat(float min, float max)
{
	return min + (((float)rand()) / ((float)RAND_MAX)) * (max - min);
}

// Returns a random integer in the range { min, ..., max } (inclusive on both ends)
int randInt(int min, int max)
{
	return min + (rand() % (max - min + 1));
}

float randIntF(int min, int max)
{
	return (float)randInt(min, max);
}
