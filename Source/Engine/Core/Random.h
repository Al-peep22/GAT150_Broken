#pragma once
#include <stdlib.h>
#include <random>
#include "../Math/Vector2.h"
#include "../Math/Math.h"
namespace viper {
	namespace random {

		//--------------------------------mt19937-----------------------------------------------
        inline std::mt19937& generator() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            return gen;
        }

        inline void seed(unsigned int value) {
            generator().seed(value);
        }
		//--------------------------------------------------------------------------------------
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        
        //---------------------------------Integers---------------------------------------------
		//inline int getRandomInt() { return rand(); }

		//inline int getRandomInt(int max) { return rand() % max + 1; }

		//inline int getRandomInt(int min, int max) { return min + getRandomInt(max - min + 1); }

        inline int getRandomInt(int min, int max) {
            std::uniform_int_distribution<> dist(min, max);
            return dist(generator());
        }

        inline int getRandomInt(int max) {
            return getRandomInt(0, max - 1);
        }

        inline int getRandomInt() {
            static std::uniform_int_distribution<> dist;
            return dist(generator());
        }
        //--------------------------------------------------------------------------------------

        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

        //------------------------------------Floats--------------------------------------------
		//inline float getRandomFloat() { return rand() / (float)RAND_MAX; }

		//inline float getRandomFloat(float max) { return rand() / (float)max; }

		//inline float getRandomFloat(float min, float max) { return min+rand() / (float)max; }

		inline float getRandomFloat(float min, float max) {
			std::uniform_real_distribution<float> dist(min, max);
			return dist(generator());
		}

		inline float getRandomFloat(float max) {
			return getRandomFloat(0.0f, max);
		}

		inline float getRandomFloat() {
			static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
			return dist(generator());
		}
        //--------------------------------------------------------------------------------------

        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

        //------------------------------Real_Numbers--------------------------------------------
                template <typename T = float>
        inline T getReal(T min, T max) {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(generator());
        }

        template <typename T = float>
        inline T getReal(T max) {
            return getReal(static_cast<T>(0), static_cast<T>(max));
        }

        template <typename T = float>
        inline T getReal() {
            static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
            return dist(generator());
        }
        //--------------------------------------------------------------------------------------

        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

        //---------------------------------Boolean----------------------------------------------
        inline bool getBool() {
            static std::bernoulli_distribution dist(0.5);
            return dist(generator());
        }
        //--------------------------------------------------------------------------------------

        inline vec2 onUnitCircle() {
            float radians = getReal(math::twoPi);
            vec2 v;
            v.x = math::cosf(radians);
			v.y = math::sinf(radians);

            return { math::cosf(radians), math::sinf(radians) };
        }
	}
}