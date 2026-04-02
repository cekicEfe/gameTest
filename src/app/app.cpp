#include <app.hpp>

RlClone::App::App(const int ScreenWidth, const int ScreenHeight,
                  const std::string WindowTitle)
    : ScreenWidth(ScreenWidth), ScreenHeight(ScreenHeight),
      WindowTitle(WindowTitle), game(RlClone::Game()) {}

RlClone::App::~App() {}

void RlClone::App::init() {
  raylib::InitWindow(this->ScreenWidth, this->ScreenHeight,
                     this->WindowTitle.data());
  raylib::DisableCursor();  // Limit cursor to relative movement inside the
                            // window
  raylib::SetTargetFPS(60); // Set our game to run at 60 frames-per-second
}

void RlClone::App::main_loop() {
  while (!raylib::WindowShouldClose()) // Detect window close button or ESC key
  {
    this->game.update(this->delta_time);
    this->game.render();
  }
}

void RlClone::App::finish() { raylib::CloseWindow(); }
