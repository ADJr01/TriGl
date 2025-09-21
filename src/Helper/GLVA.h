//
// Created by STHEP on 9/18/2025.
//
#pragma once
#ifndef TRIGL_GLVA_H
#define TRIGL_GLVA_H
#include <memory>

#include "../GLX/lib/Numeric.h"
#include "GL/glew.h"


class GLVA {
private:
    std::unique_ptr<glx_type::uint[]> VBOs = nullptr;
    glx_type::uint VAO;
    glx_type::uint MAX_VBO_SIZE = 0;
    glx_type::uint VBO_BIND_COUNTER  = 0;

public:
    GLVA(glx_type::uint total_buffer_obj) {
        this->MAX_VBO_SIZE = total_buffer_obj;
        this->VBOs = std::make_unique<glx_type::uint[]>(this->MAX_VBO_SIZE);
        glGenVertexArrays(1,&this->VAO);
        glBindVertexArray(this->VAO);
        glGenBuffers(this->MAX_VBO_SIZE,this->VBOs.get());
    }

    template <std::size_t N>
    void bindVertexInfo_F(std::array<float,N>& vertices,int attribToCount,int per_vertex_size,const void* startFrom) {
        if (this->VBO_BIND_COUNTER >= MAX_VBO_SIZE) throw std::runtime_error("Too many VBO buffer objects To Record");
        glBindBuffer(GL_ARRAY_BUFFER,this->VBOs[this->VBO_BIND_COUNTER]);
        glBufferData(GL_ARRAY_BUFFER,N*sizeof(float),vertices.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(this->VBO_BIND_COUNTER,attribToCount,GL_FLOAT,GL_FALSE,per_vertex_size*sizeof(float),const_cast<void *>(startFrom));
        glEnableVertexAttribArray(this->VBO_BIND_COUNTER);
        this->VBO_BIND_COUNTER+=1;
    }
    bool didFilledVertexAttachments() const {
        return this->VBO_BIND_COUNTER == MAX_VBO_SIZE;
    }
    template <std::size_t N>
    void bindVertexInfo_I(std::array<int,N>& vertices,int attribToCount,int per_vertex_size,const void* startFrom) {
        if (this->VBO_BIND_COUNTER >= MAX_VBO_SIZE) throw std::runtime_error("Too many VBO buffer objects To Record");
        glBindBuffer(GL_ARRAY_BUFFER,this->VBOs[this->VBO_BIND_COUNTER]);
        glBufferData(GL_ARRAY_BUFFER,N*sizeof(int),vertices.data(),GL_STATIC_DRAW);
        glVertexAttribIPointer(this->VBO_BIND_COUNTER,attribToCount,GL_INT,per_vertex_size*sizeof(int),const_cast<void *>(startFrom));
        glEnableVertexAttribArray(this->VBO_BIND_COUNTER);
        this->VBO_BIND_COUNTER+=1;
    }

    glx_type::uint& getVertexArray() {
        return this->VAO;
    }
    ~GLVA() {
        glDeleteBuffers(this->MAX_VBO_SIZE,this->VBOs.get());
        this->VBOs.reset();
        glDeleteVertexArrays(1, &this->VAO);
    }


};


#endif //TRIGL_GLVA_H