#version 330 core

in  vec3 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;
void main(){
    pixelColor=vec4(fragColor,1.0)/positionData ;
}

