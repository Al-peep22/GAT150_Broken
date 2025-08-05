#pragma once
#include <string>
#include <SDL3_ttf/SDL_ttf.h>
#include "Resources/Resource.h"

struct TTF_Font;

namespace viper {
	class Font : public Resource{
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* ttfFont{ nullptr };
	};
}