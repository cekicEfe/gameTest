#include <app.hpp>
#include <exception>

int main() {
  RlClone::App app = RlClone::App();
  
  try {
    app.Init();
  } catch (const std::overflow_error &e) {
    std::cout << "Overflow error occured :" << e.what() << std::endl;
  } catch (const std::runtime_error &e) {
    std::cout << "Runtime error occured :" << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << "An exception occured :" << e.what() << std::endl;
  } catch (...) {
    std::cout << "Something went wrong" << std::endl;
  }

  try {
    app.MainLoop();
  } catch (const std::overflow_error &e) {
    std::cout << "Overflow error occured :" << e.what() << std::endl;
  } catch (const std::runtime_error &e) {
    std::cout << "Runtime error occured :" << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << "An exception occured :" << e.what() << std::endl;
  } catch (...) {
    std::cout << "Something went wrong" << std::endl;
  }

  app.Finish();

  return 0;
}
