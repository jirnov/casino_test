// clang-format off
#include <GL/glew.h>
#include <GL/freeglut.h>
// clang-format on
#include <stb_image.h>
#include <cstdint>
#include <iostream>
#include <memory>

struct ImageData {
    std::uint8_t* pixels = nullptr;
    size_t width = 0;
    size_t height = 0;
    size_t numChannels = 0;

    ImageData(std::uint8_t* pixels, size_t width, size_t height, size_t numChannels)
       : pixels(std::move(pixels))
       , width(width)
       , height(height)
       , numChannels(numChannels)
    {}

    ~ImageData()
    {
        if (pixels) {
            stbi_image_free(pixels);
        }
    }
};

std::unique_ptr<ImageData> loadImage(const char* fileName)
{
    int width = 0;
    int height = 0;
    int numChannels = 0;

    stbi_set_flip_vertically_on_load(true);

    if (auto pixels = stbi_load(fileName, &width, &height, &numChannels, 0)) {
        return std::make_unique<ImageData>(pixels, width, height, numChannels);
    }

    std::cerr << "Cannot load pixel data from file " << fileName << "\n";
    return {};
}

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

int main(int argc, char** argv)
{
    loadImage("image1.png");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("CasinoTest");

    glutDisplayFunc(display);

    init();

    glutMainLoop();


    return 0;
}
