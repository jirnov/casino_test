// clang-format off
//#include <GL/glew.h>
//#include <GL/freeglut.h>
// clang-format on
//#include <cstdint>
#include <iostream>
//#include <memory>
#include "Application.h"

/*
void init()
{
    if (glewInit() != GLEW_OK) {
        std::cerr << "glewInit() error\n";
        exit(1);
    }
}

void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}
*/

int main(int argc, char** argv)
{
    try {
        Application app(argc, argv);
        return app.run();
    } catch (const std::exception& e) {
        std::cerr << "FATAL error: " << e.what() << "\n";
        return 1;
    }

    /*

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("CasinoTest");

    glutDisplayFunc(display);

    init();

    //auto data = loadImage("image1.png");
    //auto sprite = Sprite(std::move(data));

    glutMainLoop();

    return 0;
    */
}
