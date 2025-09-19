#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in int vertIndex;
out vec4 fragColor;
out float time;
out vec4 positionData;

uniform mat4 uniformModel;
uniform float iTime;

const vec4 Color[4] = vec4[4](
        vec4(0.26, 0.52, 0.96, 1.0), // Sky Blue
        vec4(0.99, 0.70, 0.36, 1.0), // Sunset Orange
        vec4(0.91, 0.30, 0.47, 1.0), // Rose Pink
        vec4(0.43, 0.18, 0.44, 1.0)  // Deep Purple
);

void main(){
    float x = vertPos.x;
    float y = vertPos.y;
    float z = vertPos.z;
    fragColor =  Color[vertIndex];
    time=iTime;
    vec4 finalPos = uniformModel * vec4(x,y,z,1.0);
    positionData = finalPos;
    gl_Position = finalPos;
}