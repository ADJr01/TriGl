#include<iostream>
#include <memory>

#include "./GLX/Glx.h"
const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
unsigned int program;
uint VAO, VBO;
int main() {
    GLX glx;;
    glx.buildMode(BUILD_MODE::DEV);
    //creating vertices
    float vertecies[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    glx.ShaderTool().setFragmentShaderPath(fs);
    glx.ShaderTool().setVertexShaderPath(vs);


    glx.addPostLaunchProcedure([&]() {
        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1,&VBO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertecies),vertecies,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
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