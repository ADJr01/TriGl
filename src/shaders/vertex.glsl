#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec4 vertColor;
out vec4 fragColor;
out float time;
out vec4 positionData;
out vec2 textureCoord;
uniform mat4 uniformModel;
uniform float iTime;

void main(){
    float x = vertPos.x;
    float y = vertPos.y;
    float z = vertPos.z;
    fragColor =  vertColor;
    time=iTime;
    vec4 finalPos = uniformModel * vec4(x,y,z,1.0);
    positionData = finalPos;
    gl_Position = finalPos;
}