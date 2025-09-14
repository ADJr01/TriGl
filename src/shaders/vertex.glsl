#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in int vertIndex;
out vec3 fragColor;
out float time;
out vec4 positionData;

uniform mat4 uniformModel;
uniform float iTime;

const vec3 Color[4] = vec3[4](
        vec3(0.11, 0.94, 0.56),
        vec3(0.02, 0.87, 0.36),
        vec3(0.03, 0.41, 0.83),
        vec3(0.05, 0.60, 0.41)
);

void main(){
    float x = vertPos.x;
    float y = vertPos.y;
    float z = vertPos.z;
    fragColor = Color[vertIndex];
    time=iTime;
    vec4 finalPos = uniformModel * vec4(x,y,z,1.0);
    positionData = finalPos;
    gl_Position = finalPos;
}