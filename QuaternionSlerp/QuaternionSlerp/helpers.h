/*
Title: Vector Mathematics
File Name: helpers.h
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

#include <cstdlib>

// Approximates 1/sqrt(x) to within >99% accuracy.
// Useful for quickly normalizing vectors.
float FastInvSqrt(float x);

// Returns a random real number in the interval [min, max)
float randFloat(float min, float max);

// Returns a random integer in the range { min, ..., max }
// N.B. min cannot be INT_MIN, causes divide by 0 error
int randInt(int min, int max);

// Returns a random integer in the range { min, ..., max } casted to a float
float randIntF(int min, int max);
