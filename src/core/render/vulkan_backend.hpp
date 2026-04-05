#ifndef CORE_RENDER_VULKAN_BACKEND_HPP
#define CORE_RENDER_VULKAN_BACKEND_HPP

#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif

#include <GLFW/glfw3.h>
#include <backend_interface.hpp>
#include <iostream>
#include <vector>

namespace core::render_backend {

class VulkanBackend final : public BackendInterface {
public:
  VulkanBackend();
  ~VulkanBackend();

  void InitWindowSystem() override;
  void HintWindow() override;
  void CreateWindow(unsigned int width, unsigned int height,
                    const char *title) override;

  void InitSpecial() override;
  void InitVulkan();

private:
  void CreateInstance();
  void SetupDebugMessenger();
  void PickPhysicalDevice();
  void CreateLogicalDevice();
  std::vector<const char *> getRequiredInstanceExtensions();
  static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
      vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
      vk::DebugUtilsMessageTypeFlagsEXT type,
      const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData, void *);
  bool isDeviceSuitable(vk::raii::PhysicalDevice const &physicalDevice);

public:
  bool WindowShouldClose() override;
  void WindowSystemPollEvents() override;
  void BeginDrawing() override;
  void EndDrawing() override;
  void CloseWindow() override;
  void CleanUpWindowSystem() override;

  void CleanUpVulkan();

private:
  GLFWwindow *MainWindow;
  vk::raii::Context context;
  vk::raii::Instance instance = nullptr;
  vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;

  vk::raii::PhysicalDevice physicalDevice = nullptr;
  vk::raii::Device device = nullptr;

  vk::raii::Queue graphicsQueue = nullptr;

  std::vector<const char *> requiredDeviceExtension = {
      vk::KHRSwapchainExtensionName};

  const std::vector<char const *> validationLayers = {
      "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif
  
};
} // namespace core::render_backend

#endif
