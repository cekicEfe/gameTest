#ifndef CORE_RENDER_HPP
#define CORE_RENDER_HPP

#ifdef USE_VULKAN_BACKEND
#include <vulkan_backend.hpp>
#endif

namespace core {

class Renderer {
public:
  Renderer();
  ~Renderer();

  void Init();
  void CreateWindow(unsigned int width,unsigned int height, const char *title);
  void InitSpecial();
  bool WindowShouldClose();
  
  void PollEvents();
  void BeginDrawing();
  void EndDrawing();

  void CloseWindow();
  void CleanUp();
  
private:
  #ifdef USE_VULKAN_BACKEND
  render_backend::VulkanBackend BackendRenderer;
  #endif
};

} // namespace core

#endif
