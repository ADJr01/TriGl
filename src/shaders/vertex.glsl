#version 330 core
layout (location = 0) in vec3 vertPos;
out vec3 fragColor;

void main(){
    gl_Position = vec4(vertPos,1.0);
    fragColor = vec3(0.25,0.77,0.98);
}