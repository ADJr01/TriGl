//
// Created by STHEP on 9/21/2025.
//

#include "Texture.h"

#include "GL/glew.h"

Texture::Texture(const char* pathToTexture) {
    int width,height,channels;
    glx_type::uchar* texture_data = stbi_load(pathToTexture,&width,&height,&channels,STBI_rgb_alpha);
}

Texture::~Texture() {
    glDeleteTextures(1,&this->textureID);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D,this->textureID);
}
