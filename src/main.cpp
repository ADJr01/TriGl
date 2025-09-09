#include<iostream>
#include <memory>

#include "./GLX/Glx.h"
const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
unsigned int program;
int main() {
    GLX glx;;


    glx.addPostLaunchProcedure([&]() {
        glx.ShaderTool().setFragmentShaderPath(fs);
        glx.ShaderTool().setVertexShaderPath(vs);
        glx.ShaderTool().buildProgram();
    });




    glx.onTick([]() {
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram( glx.ShaderTool().getProgram());
       glClearColor(0.3, 1., 0.7, 1.0);
    });

    glx.launch();
}