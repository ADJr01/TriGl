#include<iostream>
#include <memory>
#include "./GLX/Glx.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Helper/GLVA.h"

const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
unsigned int program;
int uniformModel,iTime;
constexpr glx_type::uint VERTEX_TO_DRAW_COUNT = 6;
float moveOffset=0.3,moveSpeedPerFrame=0.003,MaxMoveRight=0.5,MaxMoveLeft=-0.5;
bool isMovingRight=true;
void movementOffset() {
    if (isMovingRight) {
        moveOffset += moveSpeedPerFrame;
        (moveOffset >= MaxMoveRight) ?( isMovingRight = false):isMovingRight;
    } else {
        moveOffset -= moveSpeedPerFrame;
        if (moveOffset <= MaxMoveLeft) {
            moveOffset = MaxMoveLeft; // clamp
            isMovingRight = true;
        }
    }
}
int main() {
    GLX glx;
    GLVA* glva = nullptr;
    glx.setWindowTitle("TriCube");
    glx.buildMode(BUILD_MODE::DEV);
    //creating vertices
    std::array<float,18> positions = {
             //? POS
        -0.3f, -0.3f, 0.0f,//q3
        -0.3f, 0.3f, 0.0f, //q2
        0.3f, 0.3f, 0.0f, //q1
        0.3f, 0.3f, 0.0f, //q1
        0.3f, -0.3f, 0.0f, //q4
        -0.3f, -0.3f, 0.0f,//q3
    };
    std::array<int,6> index_list = {
        1,2,3,1,0,3
    };
    glx.ShaderTool().setFragmentShaderPath(fs);
    glx.ShaderTool().setVertexShaderPath(vs);

    glx.addPostLaunchProcedure([&]() {
        glva = new GLVA(2);
        glva->bindVertexInfo_F(positions,3);
        glva->bindVertexInfo_I(index_list,1);
        glx.ShaderTool().buildProgram();
        uniformModel = glGetUniformLocation(glx.ShaderTool().getProgram(),"uniformModel");
        iTime = glGetUniformLocation(glx.ShaderTool().getProgram(),"iTime");
    });

    glx.onTick([&]() {
        movementOffset(); // moving out triangle
        glUseProgram( glx.ShaderTool().getProgram());//selecting out shader program
        glBindVertexArray(glva->getVertexArray()); //selecting our current vertex array object
        //? handling Uniform
        auto Identity = glm::mat4(1.0); //  Identity Matrix
        Identity = glm::translate(Identity,glm::vec3(moveOffset,0.0f,0.0f));
        glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(Identity));
        glUniform1f(iTime,static_cast<float>(glfwGetTime()));
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

}