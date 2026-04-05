#include <app.hpp>

RlClone::App::App(const int ScreenWidth, const int ScreenHeight,
                  const std::string WindowTitle)
    : ScreenWidth(ScreenWidth), ScreenHeight(ScreenHeight),
      WindowTitle(WindowTitle), Game() {}

RlClone::App::~App() {}

void RlClone::App::Init() {
  this->Renderer.Init();
  this->Renderer.CreateWindow(ScreenWidth,ScreenHeight,WindowTitle.data());
  this->Renderer.InitSpecial();
  this->Game.InitDemo();
}

void RlClone::App::MainLoop() {
  while (!this->Renderer.WindowShouldClose()) // Detect window close button or ESC key
  {
    this->Renderer.PollEvents();
    this->Game.Update(this->DeltaTime);
    this->Game.Render();
  }
}

void RlClone::App::Finish() {
  //
  this->Renderer.CloseWindow();
  this->Renderer.CleanUp();
}
