#include<iostream>
#include <memory>
#include "./GLX/Glx.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Helper/GLVA.h"
#include "util/Transformer.h"
#include "util/Texture.h"
const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
const std::string texturePath = R"(D:/Projects/Personal/CG/TriGL/src/asset/jerry.png)";
const std::string maskTexturePath = R"(D:/Projects/Personal/CG/TriGL/src/asset/jerry_mask.png)";
unsigned int program;
int uniformModel,iTime;
Texture* texture = nullptr;
Texture* maskTexture = nullptr;
constexpr glx_type::uint VERTEX_TO_DRAW_COUNT = 6;
constexpr float toRadians = std::numbers::pi/180;
constexpr float CUBE_SIZE = 0.3;
int main() {
    GLX glx;
    glx.setVersionMajor(4);
    glx.setVersionMinor(6);
    GLVA* glva = nullptr;
    Transformer trans;
    glx.setWindowTitle("TriCube");
    //creating vertices
    std::array<float, 30> vertexAttribs = {
        //   POSITIONS        COLORS (R, G, B, A)
        -CUBE_SIZE, -CUBE_SIZE, 0.0f,   0.0f, 0.0f, // bottom-left
         CUBE_SIZE, -CUBE_SIZE, 0.0f,   1.0f, 0.0f, // bottom-right
        -CUBE_SIZE,  CUBE_SIZE, 0.0f,   0.0,  1.0, // top-left

         CUBE_SIZE, -CUBE_SIZE, 0.0f,   1.0f, 0.0f, // bottom-right
         CUBE_SIZE,  CUBE_SIZE, 0.0f,   1.0,  1.0, // top-right
        -CUBE_SIZE,  CUBE_SIZE, 0.0f,   0.0,  1.0,  // top-left
    };

    glx.ShaderTool().setFragmentShaderPath(fs);
    glx.ShaderTool().setVertexShaderPath(vs);

    glx.addPostLaunchProcedure([&]() {
        texture = new Texture(texturePath.c_str());
        maskTexture = new Texture(maskTexturePath.c_str());
        glva = new GLVA(2);
        glva->bindVertexInfo_F(vertexAttribs,3,5,(void*)0);
        glva->bindVertexInfo_F(vertexAttribs,2,2,(void*)(3*sizeof(float))); // confused: is per-vertex size should be 5 or 2 as position data only has 2 x,y pos arguments
        glx.ShaderTool().buildProgram();
        uniformModel = glGetUniformLocation(glx.ShaderTool().getProgram(),"uniformModel");
        iTime = glGetUniformLocation(glx.ShaderTool().getProgram(),"iTime");
        if (!glva->didFilledVertexAttachments())throw std::runtime_error("GLX VERTEX ATTACHMENT WAS NOT FILLED");
        //setting texture unit
        glUseProgram( glx.ShaderTool().getProgram());
        glUniform1i(glGetUniformLocation(glx.ShaderTool().getProgram(),"material"),0);
        glUniform1i(glGetUniformLocation(glx.ShaderTool().getProgram(),"materialMask"),1);

        //enable alpha blending
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    });

    glx.onTick([&]() {
        const double time = glfwGetTime();
        trans.movementOffset(); // moving out triangle
        glUseProgram( glx.ShaderTool().getProgram());//selecting out shader program
        glBindVertexArray(glva->getVertexArray()); //selecting our current vertex array object
        texture->bind(0);
        maskTexture->bind(1);
        //? handling Uniform
        auto Identity = glm::mat4(1.0); //  Identity Matrix
        //Identity = glm::translate(Identity,glm::vec3(trans.getMoveOffset(),0.0f,0.0f));
        //Identity = glm::rotate(Identity,toRadians*trans.getNextRotation(),glm::vec3(0.0f,0.0f,1.0f));
        //Identity = glm::scale(Identity,glm::vec3(1.0f*ts,1.0f*tc,1.0f));
        glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(Identity));
        glUniform1f(iTime,static_cast<float>(time));
        //? handling Rest of the Drawing functions
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays( GL_TRIANGLES,0,VERTEX_TO_DRAW_COUNT);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glBindVertexArray(0);
        glUseProgram(0);
    });
    //
        glx.buildMode(BUILD_MODE::DEV);
        glx.launch();
        glx.ShaderTool().deleteProgram();
        delete glva;
        delete texture;
        delete maskTexture;


}