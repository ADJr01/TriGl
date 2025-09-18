//
// Created by STHEP on 9/18/2025.
//
#pragma once
#ifndef TRIGL_GLVA_H
#define TRIGL_GLVA_H
#include <memory>

#include "../GLX/lib/Numeric.h"

template <typename T>
class GLVA {
private:
    std::unique_ptr<glx_type::uint[]> VBOs = nullptr;
    glx_type::uint VAO;
    bool buildComplete = false;
    glx_type::uint MAX_VBO_SIZE = 0;
    glx_type::uint BIDED_VBO_COUNTER  = 0;

public:
    GLVA(glx_type::uint total_buffer_obj) {
        this->MAX_VBO_SIZE = total_buffer_obj;
        this->VBOs = std::make_unique<glx_type::uint[]>(this->MAX_VBO_SIZE);
    }

};


#endif //TRIGL_GLVA_H