#ifndef CORE_RENDER_INTERFACE_HPP
#define CORE_RENDER_INTERFACE_HPP

#include <cstdint>

namespace core {
namespace render_backend {

class BackendInterface {
public:
  virtual void InitWindowSystem() = 0;
  virtual void HintWindow() = 0;
  virtual void CreateWindow(unsigned int width, unsigned int height, const char *title) = 0;
  virtual void InitSpecial() = 0;
  virtual bool WindowShouldClose() = 0;
  virtual void WindowSystemPollEvents() = 0;
  virtual void BeginDrawing() = 0;
  virtual void EndDrawing() = 0;
  virtual void CloseWindow() = 0;
  virtual void CleanUpWindowSystem() = 0;
};

}; // namespace render_backend
}; // namespace core

#endif
