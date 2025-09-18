#version 330 core
#define PI 3.14159265359
in  vec3 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;


void main(){
    float x = sqrt(positionData.x);
    float y = pow(positionData.y,2.);
    float len = length(vec2(positionData.x,positionData.y));
    float d = (smoothstep(y-0.01,x,len)* 0.314);
    float effect  =  sin(pow(len+time,2.0)*PI) / d;
    pixelColor =effect* vec4(fragColor,1.0);
}

