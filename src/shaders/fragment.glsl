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
    float dx =   sin( length(textureCoord ) + cos(PI) ) * time/mask;
    float effect = smoothstep(mask + 0.1,0.9,dx) - smoothstep(0.9,mask - 0.1,dx);
    fragColor =  vec4(effect * baseTexture,1.0);
}

