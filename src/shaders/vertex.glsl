#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in int vertIndex;
out vec3 fragColor;


const vec3 Color[3] = vec3[3](
        vec3(1.0, 0.0, 0.0),
        vec3(0.0, 0.0, 1.0),
        vec3(1.0, 1.0, 0.0)
);

void main(){
    gl_Position = vec4(vertPos,1.0);
    fragColor = Color[vertIndex];
}