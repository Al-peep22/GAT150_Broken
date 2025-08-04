#include "Font.h"
#include <iostream>

namespace viper {
	Font::~Font() {
		if (ttfFont != nullptr) {
			//TTF_CloseFont(ttfFont);
		}
	}

	bool Font::Load(const std::string& name, float fontSize) {
		ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (ttfFont == nullptr) {
			std::cerr << "Could not load font: " << name << std::endl;
			return false;
		}

		return true;
	}
}