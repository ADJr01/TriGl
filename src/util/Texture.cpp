//
// Created by STHEP on 9/21/2025.
//

#include "Texture.h"

#include "GL/glew.h"

Texture::Texture(const char* pathToTexture) {
    int width,height,channel;
    glx_type::uint
}

Texture::~Texture() {
    glDeleteTextures(1,&this->textureID);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D,this->textureID);
}
