#include "Application.h"
#include <iostream>

int main(int argc, char** argv)
{
    try {
        Application app(argc, argv);
        return app.run();
    } catch (const std::exception& e) {
        std::cerr << "FATAL error: " << e.what() << "\n";
        return 1;
    }
}
