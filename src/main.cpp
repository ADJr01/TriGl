#include<iostream>
#include "./GLX/Glx.h"
int main() {
    const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
    const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
    GLX glx;
    glx.ShaderTool().setFragmentShaderPath(fs);
    std::cout<<vs<<std::endl<<fs<<std::endl;
    glx.ShaderTool().logFragmentShader();
    // glx.onTick([]() {
    //     glClear(GL_COLOR_BUFFER_BIT);
    //    glClearColor(0.3, 1., 0.7, 1.0);
    // });

   // glx.launch();
}