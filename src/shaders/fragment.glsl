#version 460 core
#define PI 3.14159265359
in float time;
in vec4 positionData;
in vec2 textureCoord;
out vec4 pixelColor;
uniform sampler2D material;
uniform sampler2D materialMask;

void main(){
    vec3 baseColor = texture(material,textureCoord).rgb;
    float dx =   length(vec2(cos(PI*length(textureCoord)),sin(PI*length(textureCoord))))*sqrt(time*0.05);
    float effect = smoothstep(0.09,0.9,dx);
    pixelColor = effect*vec4(baseColor,1.0);
}

