#include<iostream>
#include "./GLX/Glx.h"
int main() {
    GLX glx;
    glx.setWindowTitle("My Window");

    glx.onTick([]() {
        glClear(GL_COLOR_BUFFER_BIT);
       glClearColor(0.3, 1., 0.7, 1.0);
    });

    glx.launch();
    glx.inf();
}