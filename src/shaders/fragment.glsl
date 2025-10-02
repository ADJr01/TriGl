#version 460 core
#define PI 3.14159265359
in float time;
in vec4 positionData;
in vec2 textureCoord;
out vec4 fragColor;
uniform sampler2D material;
uniform sampler2D materialMask;

void main(){
    float tX = positionData.x+time;
    float tY = positionData.y+ time;
    float len = length(vec2(tX,tY));
    vec3 baseTexture = texture(material,textureCoord).rgb;
    float mask = texture(materialMask,textureCoord).r * len;
    fragColor =  vec4(mask* baseTexture,1.0);
}

