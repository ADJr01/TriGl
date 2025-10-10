#version 460 core
#define PI 3.141592653589793
in float time;
in vec4 positionData;
in vec2 textureCoord;
out vec4 fragColor;
uniform sampler2D material;
uniform sampler2D materialMask;


void main(){
    vec3 baseTexture = texture(material,textureCoord).rgb;
    float mask = texture(materialMask,textureCoord).g;
    fragColor =vec4(baseTexture,1.0);
}

