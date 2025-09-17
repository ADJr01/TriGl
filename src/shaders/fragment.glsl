#version 330 core
#define PI 3.14159265359
in  vec3 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;


void main(){
    float x = positionData.x;
    float y = positionData.y;
    float len = length(vec2(positionData.x,positionData.y));
    float d = (smoothstep(positionData.y,positionData.x,len)* PI);
    float effect  =  cos(pow(len+time,2.0)*d);
    pixelColor =effect* vec4(fragColor,1.0);
}

