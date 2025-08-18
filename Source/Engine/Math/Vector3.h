#pragma once
#include "Math.h"
#include <cassert>

namespace viper{
	template<typename T>
	struct Vector3 {
		T x, y, z;

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		//T operator [] (unsigned int index) { return (index == 0) ? x : y; }
		T operator [] (unsigned int index) const { assert(index < 3);return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 3);return (&x)[index]; }

		Vector3 operator + (const Vector3& v) const { return Vector3{ x + v.x,y + v.y,z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ x - v.x,y - v.y,z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ x * v.x,y * v.y,z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ x / v.x,y / v.y,z / v.z }; }

		Vector3 operator + (float s) const { return Vector3{ x + s,y + s,z + s }; }
		Vector3 operator - (float s) const { return Vector3{ x - s,y - s,z - s }; }
		Vector3 operator * (float s) const { return Vector3{ x * s,y * s,z * s }; }
		Vector3 operator / (float s) const { return Vector3{ x / s,y / s,z / s }; }
		
		Vector3& operator += (float s) const { x + s;y + s;z + s;return *this; }
		Vector3& operator -= (float s) const { x - s;y - s;z - s;return *this; }
		Vector3& operator *= (float s) const { x* s; y* s; z* s; return *this; }
		Vector3& operator /= (float s) const { x / s;y / s;z / s;return *this; }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		//square root (x * x + y * y)
		float Lengthsqr() const { return ((x * x) + (y * y) + (z * z)); }
		float Length() const { return math::sqrtf(Lengthsqr()); }
	};

	template <typename T>
	std::ostream& operator << (std::ostream& stream, const Vector3<T>& v) {
		stream << "{" << v.x << ", " << v.y << ", " << v.z << "}";
		return stream;
	}

	template <typename T>
	std::istream& operator >> (std::istream& stream, Vector3<T>& v) {
		char ch = '\0';

		// {
		if (!(stream >> std::ws >> ch) || ch != '{') { stream.setstate(std::ios::failbit); return stream; }
		// x
		if (!(stream >> std::ws >> v.x)) { stream.setstate(std::ios::failbit); return stream; }
		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') { stream.setstate(std::ios::failbit); return stream; }
		// y
		if (!(stream >> std::ws >> v.y)) { stream.setstate(std::ios::failbit); return stream; }
		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') { stream.setstate(std::ios::failbit); return stream; }
		// z
		if (!(stream >> std::ws >> v.z)) { stream.setstate(std::ios::failbit); return stream; }
		// }
		if (!(stream >> std::ws >> ch) || ch != '}') { stream.setstate(std::ios::failbit); return stream; }

		return stream;
	}

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}