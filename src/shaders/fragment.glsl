#version 460 core
#define PI 3.141592653589793
in float time;
in vec4 positionData;
in vec2 textureCoord;
out vec4 fragColor;
uniform sampler2D material;
uniform sampler2D materialMask;
float axisSmooth(float axis,float len){
    axis = pow(axis,2.0);\
    float a = smoothstep(axis-0.01,0.9,len);
    float b = smoothstep(0.9,axis+0.01,len);
    return a-b;
}
void main(){
    vec3 baseTexture = texture(material,textureCoord).rgb;
    float mask = texture(materialMask,textureCoord).r;
    float tX = baseTexture.r*sin(time)*log(PI);
    float tY = baseTexture.g* cos(time)*log(PI);
    float len = axisSmooth(tY,length(vec2(tX,tY)));
    fragColor =  vec4(len*baseTexture,mask);
}

