#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in int vertIndex;
out vec3 fragColor;
uniform float moveX;

const vec3 Color[4] = vec3[4](
        vec3(0.11, 0.94, 0.56),
        vec3(0.02, 0.87, 0.36),
        vec3(0.03, 0.41, 0.83),
        vec3(0.05, 0.60, 0.41)
);

void main(){
    float x = vertPos.x + moveX;
    float y = vertPos.y  + sinh(moveX);
    float z = vertPos.z;
    gl_Position = vec4(x,y,z,1.0);
    fragColor = Color[vertIndex];
}