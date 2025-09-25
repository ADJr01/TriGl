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
    vec3 baseColor = texture(material,textureCoord).rgb;
    float dx = sqrt(PI*pow(textureCoord.x-positionData.x,2.0)*pow(textureCoord.y-positionData.y,2.0));
    float alpha = sin(dx * (sin((texture(materialMask,textureCoord).r * textureCoord.x)) * cos(texture(materialMask,textureCoord).g * textureCoord.y)));
    pixelColor =alpha*vec4(baseColor,1.0);
}

