#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stb_image.h>
#include <iostream>

void init() {
    if (glewInit() != GLEW_OK) {
        std::cerr << "glewInit() error\n";
        exit(1);
    }
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("CasinoTest");

    glutDisplayFunc(display);

    init();

    glutMainLoop();

    return 0;
}
