#include <app.hpp>

int main(int argc, char **argv) {

  RlClone::App app;
  app.Init();
  app.Run();
  app.Finish();
  
  
  return 0;
}
