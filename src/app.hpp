#ifndef APP_HPP
#define APP_HPP

// The reason why we import raylib like this is that
// there is a import problem between jolt and raylib
// where COLORS are ambgious
// like WHITE RED BLACK
namespace raylib {
#include <raylib.h>
}

namespace RlClone {

class App {
private:
  const int screenWidth = 800;
  const int screenHeight = 450;
  const float delta_time = 1.0f / 60.0f;

public:
  void init();
  void main_loop();
  void finish();
};

}; // namespace RlClone

#endif
