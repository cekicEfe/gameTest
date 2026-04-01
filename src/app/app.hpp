#ifndef APP_HPP
#define APP_HPP

#include <game.hpp>
#include <string>
// The reason why we import raylib like this is that
// there is a import problem between jolt and raylib
// where COLORS are ambgious
// like WHITE RED BLACK
namespace raylib {
#include <raylib.h>
}

namespace RlClone {

// class AppConfig {};

class App {
private:
  const int ScreenWidth;
  const int ScreenHeight;
  std::string WindowTitle;

  const float delta_time = 1.0f / 60.0f;
  RlClone::Game game;

public:
  App(const int ScreenWidth = 1080, const int ScreenHeight = 1920,
      const std::string WindowTitle = std::string("RlClone"));
  ~App();

  void init();
  void main_loop();
  void finish();
};

}; // namespace RlClone

#endif
