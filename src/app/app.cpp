#include <app.hpp>


RlClone::App::App(const uint ScreenWidth, const uint ScreenHeight, const std::string WindowTitle)
    : ScreenWidth(ScreenWidth)
    , ScreenHeight(ScreenHeight)
    , WindowTitle(WindowTitle)
    , Game() {

    std::cout << "LOG: Initializing app object" << std::endl;
    std::cout << "LOG: Initializing raylib" << std::endl;
    raylib::InitWindow(this->ScreenWidth, this->ScreenHeight, this->WindowTitle.data());
    raylib::SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    this->Game.Init();
    std::cout << "LOG: Initialized app object successfully" << std::endl;
}


RlClone::App::~App(){
    std::cout << "LOG: Destroying app object" << std::endl;
    this->Game.Cleanup();
    raylib::CloseWindow(); // Close window and OpenGL context
    std::cout << "LOG: Destroyed app successfully" << std::endl;
}


void RlClone::App::Run() {
    this->Game.MainLoop();
}
