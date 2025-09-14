#version 330 core
#define PI 3.14159265359
in  vec3 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;


void main(){
    float d = sqrt((pow(positionData.x,2.) + pow(positionData.y,2.))*PI);
    float blendAmount = smoothstep(0.1,time,sin(d));
    pixelColor=vec4(fragColor *blendAmount ,1.0) ;
}

