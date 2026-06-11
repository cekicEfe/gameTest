#ifndef APP_HPP
#define APP_HPP

#include <game/Game.hpp> // For RlClone::Game
#include <string> // For std::string

namespace raylib {
#include <raylib.h> 
};

namespace RlClone {

class App {
private:
    uint ScreenWidth;
    uint ScreenHeight;
    std::string WindowTitle;

    RlClone::Game Game;
public:
    App(const uint ScreenWidth = 1920,
        const uint ScreenHeight = 1080,
        const std::string WindowTitle = std::string("RlClone"));
    ~App();

    void Run();
};

} // namespace RlClone

#endif
