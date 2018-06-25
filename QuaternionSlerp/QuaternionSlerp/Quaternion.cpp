#include "Quaternion.h"

Quaternion::Quaternion()
	: w(0), x(0), y(0), z(0)
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
	: w(w), x(x), y(y), z(z)
{
}

Quaternion::Quaternion(float w, Vector3D v)
	: w(w), x(v.x), y(v.y), z(v.z)
{
}

Quaternion operator+(Quaternion q, Quaternion r)
{
	return Quaternion(q.w + r.w, q.x + r.x, q.y + r.y, q.z + r.z);
}

Quaternion operator-(Quaternion q)
{
	return Quaternion(-q.w, -q.x, -q.y, -q.z);
}

Quaternion operator-(Quaternion q, Quaternion r)
{
	return q + (-r);
}

Quaternion operator*(Quaternion q, Quaternion r)
{
	float wComp = (q.w * r.w) - (q.x * r.x) - (q.y * r.y) - (q.z * r.z);
	float xComp = (q.w * r.x) + (q.x * r.w) - (q.y * r.z) + (q.z * r.y);
	float yComp = (q.w * r.y) + (q.x * r.z) + (q.y * r.w) - (q.z * r.x);
	float zComp = (q.w * r.z) - (q.x * r.y) - (q.y * r.x) + (q.z * r.w);

	return Quaternion(wComp, xComp, yComp, zComp);
}

Quaternion operator*(float s, Quaternion q)
{
	return Quaternion(s*q.w, s*q.x, s*q.y, s*q.z);
}

Quaternion operator*(Quaternion q, float s)
{
	return s * q;
}

float Norm(Quaternion q)
{
	return (q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
}

float Magnitude(Quaternion q)
{
	return (sqrt(Norm(q)));
}

Quaternion operator/(Quaternion q, float s)
{
	return Quaternion(q.w / s, q.x / s, q.y / s, q.z / s);
}

Quaternion operator/(Quaternion q, Quaternion r)
{
	float norm = Norm(r);

	Quaternion q = q * r;

	return Quaternion(q / norm);
}

Quaternion Normalize(Quaternion q)
{
	return (q / Magnitude(q));
}

Quaternion Conjugate(Quaternion q)
{
	return Quaternion(q.w, -q.x, -q.y, -q.y);
}

Quaternion Inverse(Quaternion q)
{
	return(Conjugate(q) / Norm(q));
}

float Dot(Quaternion q, Quaternion r)
{
	return ((q.w*r.w) + (q.x*r.x) + (q.y*r.y) + (q.z*r.z));
}

float AngleBetweenQuaternions(Quaternion q, Quaternion r)
{
	float cosOfAngle = Dot(q, r) / (Magnitude(q) * Magnitude(r));

	return (acos(cosOfAngle));
}

Quaternion Rotation(Vector3D v, float a)
{
	v = Normalize(v);

	return Quaternion(cos(a / 2), (sin(a / 2) * v));
}

Quaternion Slerp(Quaternion a, Quaternion b, double t)
{
	Quaternion q = Quaternion();

	// Calculate angle between them
	double cosHalfTheta = (a.w * b.w) + (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	if (abs(cosHalfTheta) >= 1.0)
	{
		q.w = a.w;
		q.x = a.x;
		q.y = a.y;
		q.z = a.z;

		return q;
	}

	// Calculate temporary values
	double halfTheta = acos(cosHalfTheta);
	double sinHalfTheta = sqrt(1.0f - cosHalfTheta * cosHalfTheta);

	// if theta = 180 degrees then result is not fully defined
	// we could rotate around any axis normal to a or b
	if (fabs(sinHalfTheta) < 0.001)
	{
		q.w = (a.w * 0.5 + b.w * 0.5);
		q.x = (a.x * 0.5 + b.x * 0.5);
		q.y = (a.y * 0.5 + b.y * 0.5);
		q.z = (a.z * 0.5 + b.z * 0.5);

		return q;
	}

	double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
	double ratioB = sin(t * halfTheta) / sinHalfTheta;

	// Calculate Quaternion
	q.w = (a.w * ratioA + b.w * ratioB);
	q.x = (a.x * ratioA + b.x * ratioB);
	q.y = (a.y * ratioA + b.y * ratioB);
	q.z = (a.z * ratioA + b.z * ratioB);

	return q;
}

Matrix3D RotationMatrix(Quaternion q)
{
	float n00 = 1 - (2 * q.y*q.y) - (2 * q.z*q.z);
	float n01 = 2 * ((q.x * q.y) + (q.w * q.z));
	float n02 = 2 * ((q.x * q.z) - (q.w * q.y));
	float n10 = 2 * ((q.x * q.y) - (q.w * q.z));
	float n11 = 1 - (2 * q.x*q.x) - (2 * q.z*q.z);
	float n12 = 2 * ((q.y * q.z) + (q.w * q.x));
	float n20 = 2 * ((q.x * q.z) + (q.w * q.y));
	float n21 = 2 * ((q.y * q.z) - (q.w * q.x));
	float n22 = 1 - (2 * q.x*q.x) - (2 * q.y*q.y);

	return Matrix3D(n00, n01, n02,
		n10, n11, n12,
		n20, n21, n22);
}

Vector3D RotateVector(Vector3D v, Quaternion q)
{
	Matrix3D rotationMatrix = RotationMatrix(q);

	return rotationMatrix * v;
}

std::ostream& operator<<(std::ostream& os, Quaternion q)
{
	os << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
	return os;
}