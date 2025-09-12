#version 330 core

in  vec3 fragColor;
in float time;
in vec2 positionData;
out vec4 pixelColor;
void main(){
    vec2 R = positionData.xy;
    vec2 uv = (2. * positionData - R) / R.y;
    float iTime = time;
    float r = fragColor.r;
    float g = fragColor.g;
    float b = fragColor.b;
    float d = length(uv);
    //float c = smoothstep(sin(uv.x*iTime),cos(iTime*uv.y),d);
    r*=d;
    g*=d;
    b*=d;
    //pixelColor = vec4(r,g,b,1.0);
    pixelColor=vec4(d*0.25);
}