#ifndef APP_HPP
#define APP_HPP

#include <game.hpp>
#include <string>
#include <render.hpp>

namespace RlClone {

// class AppConfig {};

class App {
private:
  const int ScreenWidth;
  const int ScreenHeight;
  std::string WindowTitle;

  const float DeltaTime = 1.0f / 60.0f;
  RlClone::Game Game;
  core::Renderer Renderer;
  
public:
  App(const int ScreenWidth = 1920, const int ScreenHeight = 1080,
      const std::string WindowTitle = std::string("RlClone"));
  ~App();

  void Init();
  void MainLoop();
  void Finish();
};

} // namespace RlClone

#endif
