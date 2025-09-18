#include<iostream>
#include <memory>
#include "./GLX/Glx.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const std::string vs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/vertex.glsl)";
const std::string fs = R"(D:/Projects/Personal/CG/TriGL/src/shaders/fragment.glsl)";
unsigned int program;
glx_type::uint VAO;
int uniformModel,iTime;
std::array<glx_type::uint,2> VBOs;
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
        0,2,3,1,0,1
    };
    glx.ShaderTool().setFragmentShaderPath(fs);
    glx.ShaderTool().setVertexShaderPath(vs);

    glx.addPostLaunchProcedure([&]() {
        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);
        glGenBuffers(VBOs.size(),VBOs.data());
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
        uniformModel = glGetUniformLocation(glx.ShaderTool().getProgram(),"uniformModel");
        iTime = glGetUniformLocation(glx.ShaderTool().getProgram(),"iTime");
    });

    glx.onTick([&]() {
        movementOffset(); // moving out triangle
        glUseProgram( glx.ShaderTool().getProgram());//selecting out shader program
        glBindVertexArray(VAO); //selecting our current vertex array object
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

    glx.launch();
    glx.ShaderTool().deleteProgram();
}