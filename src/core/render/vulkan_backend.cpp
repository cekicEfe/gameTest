#include "vulkan_backend.hpp"

using namespace core::render_backend;

VulkanBackend::VulkanBackend() {}

VulkanBackend::~VulkanBackend() {}

void VulkanBackend::InitWindowSystem() {
  //
  glfwInit();
}

void VulkanBackend::HintWindow() {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void VulkanBackend::CreateWindow(unsigned int width, unsigned int height,
                                 const char *title) {
  this->MainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void VulkanBackend::InitSpecial() {
  this->InitVulkan();
  this->SetupDebugMessenger();
  this->PickPhysicalDevice();
}

void VulkanBackend::InitVulkan() {
  std::cout << "LOG: Initializing Vulkan \n";
  std::cout << "LOG: Initalized Vulkan!\n";
}

void VulkanBackend::CreateInstance(){

}

void VulkanBackend::SetupDebugMessenger() {

}

void VulkanBackend::PickPhysicalDevice() {

}

void VulkanBackend::CreateLogicalDevice() {

};

std::vector<const char *> VulkanBackend::getRequiredInstanceExtensions() {
}

VKAPI_ATTR vk::Bool32 VKAPI_CALL VulkanBackend::debugCallback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
    vk::DebugUtilsMessageTypeFlagsEXT type,
    const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData, void *) {
}

bool VulkanBackend::isDeviceSuitable(
    vk::raii::PhysicalDevice const &physicalDevice) {
}

bool VulkanBackend::WindowShouldClose() {
  return glfwWindowShouldClose(this->MainWindow);
}

void VulkanBackend::WindowSystemPollEvents() {
  //
  glfwPollEvents();
}

void VulkanBackend::BeginDrawing() {}

void VulkanBackend::EndDrawing() {}

void VulkanBackend::CloseWindow() {
  //
  glfwDestroyWindow(this->MainWindow);
}
void VulkanBackend::CleanUpWindowSystem() {
  //
  glfwTerminate();
}

void VulkanBackend::CleanUpVulkan() {}
