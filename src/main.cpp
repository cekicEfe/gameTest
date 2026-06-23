#include <game/Game.hpp> // For RlClone::App
#include <exception> // For std::exception
#include <iostream> // For std::cout and std::endl

int main(int argc, char** argv) {
    try {
        RlClone::Game game;
        game.Run();
    } catch (std::exception &e) {
        std::cout << "Something went very wrong" << std::endl;
        std::cout << e.what() << std::endl;
        // Cannot continue abort
        return 1;
    }

    
    return 0;
}
