#include <app.hpp>
#include <exception>

int main() {
  RlClone::App app = RlClone::App(1920, 1080, "This is an app title !!!");

  try {
    app.Init();
  } catch (const std::overflow_error &e) {
    std::cout << "Overflow error occured :" << e.what() << std::endl;

    app.Finish();
    return -1;
  } catch (const std::runtime_error &e) {
    std::cout << "Runtime error occured :" << e.what() << std::endl;

    app.Finish();
    return -1;
  } catch (const std::exception &e) {
    std::cout << "An exception occured :" << e.what() << std::endl;

    app.Finish();
    return -1;
  } catch (...) {
    std::cout << "Something went wrong" << std::endl;

    app.Finish();
    return -1;
  }

  try {
    app.MainLoop();
  } catch (const std::overflow_error &e) {
    std::cout << "Overflow error occured :" << e.what() << std::endl;

    app.Finish();
    return -1;
  } catch (const std::runtime_error &e) {
    std::cout << "Runtime error occured :" << e.what() << std::endl;

    app.Finish();
    return -1;
  } catch (const std::exception &e) {
    std::cout << "An exception occured :" << e.what() << std::endl;

    app.Finish();
    return -1;
  } catch (...) {
    std::cout << "Something went wrong" << std::endl;

    app.Finish();
    return -1;
  }

  app.Finish();

  return 0;
}
