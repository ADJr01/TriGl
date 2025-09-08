#include<iostream>
#include "./GLX/Glx.h"
int main() {
    GLX glx;
    glx.setWindowTitle("My Window");
    glx.inf();
    glx.launch();
}