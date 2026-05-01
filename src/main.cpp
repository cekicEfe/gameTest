#include <app.hpp>

#include <exception> // For exceptions
#include <iostream> // For cout and endl

int main(int argc, char** argv) {
    RlClone::App app;

    try {
        app.Run();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
