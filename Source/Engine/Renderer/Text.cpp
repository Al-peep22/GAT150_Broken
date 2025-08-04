#include "Text.h"

namespace viper {
	Text::~Text() {
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
		}
	}

	bool Text::Create(Renderer& renderer, const std::string& text, const vec3& color) {
		// create a surface using the font, text string and color
		SDL_Color c{ (uint8_t)(color.x * 255), (uint8_t)(color.y * 255), (uint8_t)(color.z * 255), 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font->ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {
			std::cerr << "Could not create surface.\n";
			return false;
		}

		// create a texture from the surface, only textures can render to the renderer
		texture = SDL_CreateTextureFromSurface(renderer.renderer, surface);
		if (texture == nullptr) {
			SDL_DestroySurface(surface);
			std::cerr << "Could not create texture" << SDL_GetError() << std::endl;
			return false;
		}

		// free the surface, no longer needed after creating the texture
		SDL_DestroySurface(surface);

		return true;
	}

	void Text::Draw(Renderer& renderer, float x, float y) {
		// get the texture width and height
		float width, height;
		bool success = SDL_GetTextureSize(texture, &width, &height);
		assert(success);

		// set the texture into the renderer at rect 
		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer.renderer, texture, NULL, &rect);
		assert(success);
	}
}