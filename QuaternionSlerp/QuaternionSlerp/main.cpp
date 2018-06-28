/*
Title: Quaternion Mathematics
File Name: main.cpp
Copyright © 2016
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

// The primary objective is to study the operations of Quaternions
#include "Quaternion.h"
#include <iostream>

int main()
{
	// The general for the quaternion expression is
	// q = w + xi + yj + zk, where w, x, y, z are real numbers
	// and i, j, k are imaginary numbers

	// According to the Hamiltion's famous expression
	// i^2 = j^2 = k^2 = -1

	// Quaternions can also be represented as an ordered pair
	// q = [s, v] where s is real number and v is Vector3D 
	// similar to q = [s, xi + yj + zk] where x, y, z are obtained from Vector v

	Quaternion q = Quaternion(10, 1, 1, 4);
	Quaternion l = Quaternion(10, 4, 5, 9);

	float s = 10.0f;
	float r = 5.0f;

	std::cout << "======THE QUATERNION OPERATIONS======" << std::endl;

	std::cout << "The sum of two Quaternions: " << std::endl;
	std::cout << q + l << std::endl;

	std::cout << "The difference of two Quaternions: " << std::endl;
	std::cout << q - l << std::endl;

	std::cout << "The product of two Quaternions: " << std::endl;
	std::cout << q * l << std::endl;

	std::cout << "The division of two Quaternions: " << std::endl;
	std::cout << q / l << std::endl;

	std::cout << "Conjugate of the Quaternion is: " << std::endl;
	std::cout << Conjugate(q) << std::endl;

	std::cout << "The inverse of the Quaternion is: " << std::endl;
	std::cout << Inverse(q) << std::endl;

	std::cout << "The dot product of two Quaternions is: " << std::endl;
	std::cout << Dot(q, l) << std::endl;

	std::cout << "The angle between the two Quaternions is: " << std::endl;
	std::cout << AngleBetweenQuaternions(q, l) << std::endl;

	std::cout << "Generate the rotation quaternion from the vector and the angle provided: " << std::endl;
	std::cout << "The rotation quaternion is: " << std::endl;
	Quaternion rotationQuaternion = Rotation(Vector3D(0, 0, 1), 3.14 / 2);
	std::cout << rotationQuaternion << std::endl;

	std::cout << "Rotate the Vector using rotation matrix: " << std::endl;
	Vector3D vectorToRotate = Vector3D(1, 1, 1);
	Vector3D rotatedVector = RotateVector(vectorToRotate, rotationQuaternion);
	std::cout << "The rotated Vector is: " << std::endl;
	std::cout << rotatedVector << std::endl;

	std::cin.get();
}