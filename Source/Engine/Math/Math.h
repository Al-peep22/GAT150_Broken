#pragma once
#include <algorithm>
#include <cmath>

namespace viper {
	namespace math {
		const float pi = 3.14f;
		const float twoPi = 2.0f * pi;
		const float halfPi = pi / 2.0f;

		/// <summary>
		/// Converts an angle from randians to degrees;
		/// </summary>
		/// <param name="rad">The anagle in randians to converts.</param>
		/// <returnsThe equivalent angle in degrees. </returns>
		constexpr float radToDeg(float rad) { return rad * (180 / pi); }
		
		/// <summary>
		/// Converts an angle from degrees to radians;
		/// </summary>
		/// <param name="deg">The anagle in degrees to converts.</param>
		/// <returnsThe angle in radians. </returns>
		constexpr float degToRad(float deg) { return deg * (pi / 180); }


		constexpr int wrap(int value, int min, int max) {
			//if (value > min);
			int range = max - min; // calculate range of map
			int result = (value - min) % range; // shift value so range starts at 0
			if (result < 0) result += range; // wrap forward if result is negative (value)
			return min + result; // shift the result back to [min, max) range
		}

		inline float wrap(float value, float min, float max) {
			float range = max - min; // calculate range of map
			float result = std::fmod(value - min, range); // shift value so range starts at 0
			if (result < 0) result += range; // wrap forward if result is negative (value)
			return min + result; // shift the result back to [min, max) range
		}

		template<typename T >
		inline T sign(T v) {
			return (v < 0) ? (T) - 1 : (v > 0) ? (T)1 : (T)0;
		}

		using std::min;
		using std::max;
		using std::sqrt;
		using std::sqrtf;
		using std::sin;
		using std::sinf;
		using std::cos;
		using std::cosf;
		using std::acos;
		using std::acosf;

		//using std::clamp;
		/*template <typename T>
		T min(T a, T b) {
			return std::min(a, b);

			return (a < b) ? a : b;

			if (a < b) { return a; }
			else { return b; }
		}*/

		using std::atan2;
		using std::atan2f;
	}
}