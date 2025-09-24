#version 460 core
#define PI 3.14159265359
in  vec4 fragColor;
in float time;
in vec4 positionData;
in vec2 textureCoord;
out vec4 pixelColor;
uniform sampler2D material;
uniform sampler2D materialMask;

void main(){
    vec3 baseColor = sqrt(time*length(positionData.xy))*texture(material,textureCoord).rgb;
    float alpha = texture(materialMask,textureCoord).r;
    pixelColor =vec4(baseColor,alpha);
}

