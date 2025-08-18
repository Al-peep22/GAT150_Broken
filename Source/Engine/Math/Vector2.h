#pragma once
#include "Math.h"
#include <cassert>

namespace viper {
	template<typename T>
	struct Vector2 {
		T x, y;

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		//T operator [] (unsigned int index) { return (index == 0) ? x : y; }
		T operator [] (unsigned int index) const { assert(index < 2);return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2);return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x,y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x,y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x,y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x,y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s,y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s,y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s,y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s,y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }
		
		Vector2& operator += (float s) { x += s;y += s;return *this; }
		Vector2& operator -= (float s) { x -= s;y -= s;return *this; }
		Vector2& operator *= (float s) { x *= s;y *= s;return *this; }
		Vector2& operator /= (float s) { x /= s;y /= s;return *this; }

		//square root (x * x + y * y)
		float Lengthsqr() const { return ((x * x) + (y * y)); }
		float Length() const { return math::sqrtf(Lengthsqr()); }

		/// <summary>
		/// returns a normalized (unit length)
		/// </summary>
		/// <returns></returns>
		Vector2 Normalized() const { return *this / Length(); }

		/// <summary>
		///  Calculates the angle of the vector in radians.
		/// </summary>
		/// <returns></returns>
		float Angle() const { return math::atan2f(y, x); };

		Vector2 Rotate(float radians) const {
			Vector2 v;

			v.x = x * math::cosf(radians) - y * math::sinf(radians);
			v.y = x * math::sinf(radians) + y * math::cosf(radians);

			return v;
		}

		static float Dot(const Vector2& a, const Vector2& b) {
			return a.x * b.x * a.y * b.y;
		}

		static float Cross(const Vector2& a, const Vector2& b) {
			return (a.x * b.y) - (a.y * b.x);
		}

		static float AngleBetween(const Vector2& a, const Vector2& b) {
			return math::acosf(Dot(a, b));
		}

		static float SignedAngleBetween(const Vector2& a, const Vector2& b) {
			Vector2 v{ Dot(a,b), Cross(a,b) };
			return v.Angle();
		}
	};

	template <typename T>
	std::ostream& operator << (std::ostream& stream, const Vector2<T>& v) {
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}

	template <typename T>
	std::istream& operator >> (std::istream& stream, Vector2<T>& v) {
		char ch = '\0';

		// {
		if (!(stream >> std::ws >> ch) || ch != '{') { stream.setstate(std::ios::failbit); return stream; }
		// x
		if (!(stream >> std::ws >> v.x)) { stream.setstate(std::ios::failbit); return stream; }
		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') { stream.setstate(std::ios::failbit); return stream; }
		// y
		if (!(stream >> std::ws >> v.y)) { stream.setstate(std::ios::failbit); return stream; }
		// }
		if (!(stream >> std::ws >> ch) || ch != '}') { stream.setstate(std::ios::failbit); return stream; }

		return stream;
	}

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}