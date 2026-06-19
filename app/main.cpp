#include "application.h"

#include <exception>
#include <iostream>

int main(int argc, char* argv[])
{
    Application app;

    try {
        app.configure();
        return app.start(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << "An exception handled: " << e.what() << '\n';
        return -1;
    }
    catch (...) {
        std::cerr << "An unknown exception\n";
        return -2;
    }
}