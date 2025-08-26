#pragma once
#include <string>

namespace viper {
	inline std::string toLower(const std::string& str) {
		std::string result = str;
		// convert to lowercase
		for (char& c : result) {
			c = std::tolower(c);
		}
		return result;
	}

	inline std::string toUpper(const std::string& str) {
		std::string result = str;
		// convert to uppercase
		for (char& c : result) {
			c = std::toupper(c);
		}
		return result;
	}

	inline bool equalsIgnoreCase(const std::string& str1, const std::string& str2) {
		if (str1.length() != str2.length()) return false;

		return toLower(str1) == toLower(str2);

		return std::equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
			return (std::tolower(a) == std::tolower(b));
		});
	}
}