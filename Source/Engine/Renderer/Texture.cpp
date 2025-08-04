#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>
#include "Texture.h"
#include "Renderer.h"
#include "../Math/Vector2.h"
namespace viper {  

    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (texture) SDL_DestroyTexture(texture);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        texture = SDL_CreateTextureFromSurface(renderer.renderer,surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!texture)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

   vec2 Texture::GetSize()  
   {  
       // https://wiki.libsdl.org/SDL3/SDL_GetTextureSize
       if (!texture) {
		   std::cerr << "Texture not loaded." << std::endl;
           return vec2{ 0, 0 };
       }

       float width, height;  
       SDL_GetTextureSize(texture, &width, &height);  
       return vec2{ width, height };  
   }  
}