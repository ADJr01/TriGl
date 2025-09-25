//
// Created by STHEP on 9/21/2025.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../GLX/lib/prefefs.h"
#include "GL/glew.h"

Texture::Texture(const char* pathToTexture) {
    int width,height,channels;
    glx_type::uchar* texture_pixels = stbi_load(pathToTexture,&width,&height,&channels,STBI_rgb_alpha);
    //create texture
    glGenTextures(1,&this->textureID);
    LOG("Generated Texture ID: ${}",this->textureID);
    glBindTexture(GL_TEXTURE_2D,this->textureID);

    glTexImage2D(GL_TEXTURE_2D,     //upload to GPU
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texture_pixels);
    stbi_image_free(texture_pixels);    //free memory

    //configuring sampler
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D,0);
    glDeleteTextures(1,&this->textureID);
}

void Texture::bind(glx_type::uint textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D,this->textureID);
}
