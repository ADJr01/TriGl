#include<iostream>
#include <memory>

#include "./GLX/Glx.h"
const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
unsigned int program;
uint VAO;
std::array<uint,2> VBOs;
int main() {
    GLX glx;;
    glx.buildMode(BUILD_MODE::DEV);
    //creating vertices
    std::array<float,9> positions = {
             //? POS         //?COLOR
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };
    std::array<int,3> index_list = {
        1,0,2,
    };
    glx.ShaderTool().setFragmentShaderPath(fs);
    glx.ShaderTool().setVertexShaderPath(vs);


    glx.addPostLaunchProcedure([&]() {
        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);
        glGenBuffers(2,VBOs.data());
        //?position
        glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER,positions.size()*sizeof(float),positions.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);

        //?Color
        glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER,index_list.size()*sizeof(float),index_list.data(),GL_STATIC_DRAW);
        glVertexAttribIPointer(1,1,GL_INT,sizeof(float),(void*)0);
        glEnableVertexAttribArray(1);


        glx.ShaderTool().buildProgram();

    });


    glx.onTick([&]() {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram( glx.ShaderTool().getProgram());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glBindVertexArray(0);
        glUseProgram(0);
    });

    glx.launch();
    glx.ShaderTool().deleteProgram();
}