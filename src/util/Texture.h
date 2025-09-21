//
// Created by STHEP on 9/21/2025.
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../GLX/lib/Numeric.h"

#ifndef TRIGL_TEXTURE_H
#define TRIGL_TEXTURE_H


class Texture {
private:
   glx_type::uint textureID;

public:
   Texture(const char* pathToTexture);
   ~Texture();

   void bind();
};


#endif //TRIGL_TEXTURE_H