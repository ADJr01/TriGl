#include<iostream>
#include "./GLX/Glx.h"
int main() {
    const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
    const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
    GLX glx;
    glx.ShaderTool().setFragmentShaderPath(fs);
    glx.ShaderTool().setVertexShaderPath(vs);

    glx.ShaderTool().logFragmentShader();
    glx.ShaderTool().logVertexShader();
    glx.onTick([]() {
        glClear(GL_COLOR_BUFFER_BIT);
       glClearColor(0.3, 1., 0.7, 1.0);
    });

    glx.launch();
}