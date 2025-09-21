//
// Created by STHEP on 9/21/2025.
//

#include "Texture.h"

#include "GL/glew.h"

Texture::Texture(const char* pathToTexture) {
    int width,height,channels;
    glx_type::uchar* texture_pixels = stbi_load(pathToTexture,&width,&height,&channels,STBI_rgb_alpha);
    //create texture
    glCreateTextures(GL_TEXTURE_2D,1,&this->textureID);

    //upload to GPU
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_pixels);
}

Texture::~Texture() {
    glDeleteTextures(1,&this->textureID);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D,this->textureID);
}
