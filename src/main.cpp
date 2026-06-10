#include <app/App.hpp> // For RlClone::App

#include <exception> // For std::exception
#include <iostream> // For std::cout and std::endl

int main(int argc, char** argv) {
    RlClone::App app;

    try {
        app.Run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
