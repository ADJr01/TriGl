#version 460 core
#define PI 3.14159265359
in float time;
in vec4 positionData;
in vec2 textureCoord;
out vec4 fragColor;
uniform sampler2D material;
uniform sampler2D materialMask;

void main(){
    vec3 baseTexture = texture(material,textureCoord).rgb;
    float mask = texture(materialMask,textureCoord).r;
   // float dx =   length(vec2(cos(PI*length(textureCoord)),sin(PI*length(textureCoord))))*sqrt(time*0.05);
    //float effect = smoothstep(0.09,0.9,dx) - smoothstep(0.9,0.09,dx);
    fragColor =  vec4(mask * baseTexture,1.0);
}

