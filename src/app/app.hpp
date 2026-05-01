#ifndef APP_HPP
#define APP_HPP


#include <game.hpp>
#include <string>
// #include <render.hpp>


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
    // core::Renderer Renderer;
public:
    App(const uint ScreenWidth = 1920,
        const uint ScreenHeight = 1080,
        const std::string WindowTitle = std::string("RlClone"));
    ~App();

    void Run();
};


} // namespace RlClone

#endif
