#version 330 core
#define PI 3.14159265359
in  vec4 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;


void main(){
//    float x = pow(positionData.x,2.);
//    float y = pow(positionData.y,2.);
//    float d = sqrt(x+y);
//    float dx = sin(PI*time / d);
//    float effect = smoothstep(0.1,dx-0.1,dx);
    pixelColor = fragColor;
}

