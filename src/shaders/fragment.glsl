#version 330 core
#define PI 3.14159265359
in  vec3 fragColor;
in float time;
in vec4 positionData;
out vec4 pixelColor;


void main(){
    float x = positionData.x;
    float y = positionData.y;
    float d = length(vec2(positionData.x,positionData.y));
    float c = smoothstep(0.5,.09,d);
    float blendAmount = smoothstep(PI/d,d,sinh(d*time));
    vec3 ColorG =  vec3(0.0, smoothstep(0.0,0.8,cos(d*c))/d, blendAmount);
    vec3 ColorB =  vec3(vec2(blendAmount), smoothstep(0.0,0.8,cos(d*c))/d);
    vec3 finalColor = mix(ColorB-ColorG,ColorB+ColorG,sin(time * 1.5) * 0.2 + 0.8); // random experimnet with color and blend effect
    pixelColor =   vec4(ColorB*ColorG*fragColor,1.);
}

