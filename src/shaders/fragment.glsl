#version 330 core
#define PI 3.14159265359
in  vec4 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;


void main(){
    //float x = pow(positionData.x,2.);
    //float y = pow(positionData.y,2.);
    //float d = sqrt(x+y);
    //float effect = sin(PI*time / d);
    pixelColor = fragColor;
}

