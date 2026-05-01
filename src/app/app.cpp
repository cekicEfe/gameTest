#include <app.hpp>


RlClone::App::App(const uint ScreenWidth, const uint ScreenHeight, const std::string WindowTitle)
    : ScreenWidth(ScreenWidth)
    , ScreenHeight(ScreenHeight)
    , WindowTitle(WindowTitle)
    , Game() {
    raylib::InitWindow(this->ScreenWidth, this->ScreenHeight, this->WindowTitle.data());
    raylib::SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    this->Game.Init();
}


RlClone::App::~App() {
    this->Game.Cleanup();
    raylib::CloseWindow(); // Close window and OpenGL context
}


void RlClone::App::Run() {
    this->Game.MainLoop();
}
