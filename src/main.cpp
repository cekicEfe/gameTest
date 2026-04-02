#include <app.hpp>

int main() {
  RlClone::App app = RlClone::App();

  app.init();
  app.main_loop();
  app.finish();

  return 0;
}
