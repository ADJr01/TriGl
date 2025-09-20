#include<iostream>
#include <memory>
#include "./GLX/Glx.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Helper/GLVA.h"
#include "util/Transformer.h"

const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
unsigned int program;
int uniformModel,iTime;
constexpr glx_type::uint VERTEX_TO_DRAW_COUNT = 6;
constexpr float toRadians = std::numbers::pi/180;

int main() {
    Transformer trans;
    GLX glx;
    GLVA* glva = nullptr;
    glx.setWindowTitle("TriCube");
    glx.buildMode(BUILD_MODE::DEV);
    //creating vertices
    std::array<float, 42> vertexAttribs = {
        //   POSITIONS        COLORS (R, G, B, A)
        -0.3f, -0.3f, 0.0f,   1.0f, 0.2f, 0.4f, 1.0f, // bottom-left (reddish)
         0.3f, -0.3f, 0.0f,   1.0f, 0.4f, 0.6f, 1.0f, // bottom-right
        -0.3f,  0.3f, 0.0f,   0.9f, 0.5f, 0.7f, 1.0f, // top-left (pinkish)

         0.3f, -0.3f, 0.0f,   1.0f, 0.4f, 0.6f, 1.0f, // bottom-right
         0.3f,  0.3f, 0.0f,   1.0f, 0.7f, 0.8f, 1.0f, // top-right (light pink)
        -0.3f,  0.3f, 0.0f,   0.9f, 0.5f, 0.7f, 1.0f  // top-left
    };

    glx.ShaderTool().setFragmentShaderPath(fs);
    glx.ShaderTool().setVertexShaderPath(vs);

    glx.addPostLaunchProcedure([&]() {
        glva = new GLVA(2);
        glva->bindVertexInfo_F(vertexAttribs,3,7,(void*)0);
        glva->bindVertexInfo_F(vertexAttribs,4,7,(void*)(3*sizeof(float)));
        glx.ShaderTool().buildProgram();
        uniformModel = glGetUniformLocation(glx.ShaderTool().getProgram(),"uniformModel");
        iTime = glGetUniformLocation(glx.ShaderTool().getProgram(),"iTime");
        if (!glva->didFilledVertexAttachments())throw std::runtime_error("GLX VERTEX ATTACHMENT WAS NOT FILLED");

    });

    glx.onTick([&]() {
        const double time = glfwGetTime();
        trans.movementOffset(); // moving out triangle
        glUseProgram( glx.ShaderTool().getProgram());//selecting out shader program
        glBindVertexArray(glva->getVertexArray()); //selecting our current vertex array object
        //? handling Uniform
        auto Identity = glm::mat4(1.0); //  Identity Matrix
        Identity = glm::translate(Identity,glm::vec3(trans.getMoveOffset(),0.0f,0.0f));
        Identity = glm::rotate(Identity,toRadians*trans.getNextRotation(),glm::vec3(0.0f,0.0f,1.0f));
        //Identity = glm::scale(Identity,glm::vec3(1.0f*ts,1.0f*tc,1.0f));
        glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(Identity));
        glUniform1f(iTime,static_cast<float>(time));
        //? handling Rest of the Drawing functions
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays( GL_TRIANGLES,0,VERTEX_TO_DRAW_COUNT);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glBindVertexArray(0);
        glUseProgram(0);
    });
    //

        glx.launch();
        glx.ShaderTool().deleteProgram();
        delete glva;


}