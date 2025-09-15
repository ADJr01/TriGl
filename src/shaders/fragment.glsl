#version 330 core
#define PI 3.14159265359
in  vec3 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;


void main(){
    float d = sqrt((pow(positionData.x,length(positionData.x)) * pow(positionData.y,length(positionData.y))));
    float blendAmount = smoothstep(0.5,d,sinh(d*time));
    pixelColor=vec4(fragColor * blendAmount ,1.0) ;
}

