#include "Font.h"
#include <iostream>
#include "Core/Logger.h"

namespace viper {
	Font::~Font() {
		if (ttfFont != nullptr) {
			TTF_CloseFont(ttfFont);
		}
	}

	bool Font::Load(const std::string& name, float fontSize) {
		ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (ttfFont == nullptr) {
			Logger::Warning("Could not load font: {}", name);
			return false;
		}

		return true;
	}
}