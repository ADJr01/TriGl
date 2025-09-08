#version 330 core


in  ve3 fragColor;
out vec4 pixelColor;
void main(){
    pixelColor = vec4(fragColor,1.0);
}