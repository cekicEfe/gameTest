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
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
}

void VulkanBackend::CreateWindow(unsigned int width, unsigned int height,
                                 const char *title) {
  this->MainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void VulkanBackend::InitSpecial() { this->InitVulkan(); }

void VulkanBackend::InitVulkan() {
  std::cout << "LOG: Initializing Vulkan \n";
  this->CreateInstance();
  this->SetupDebugMessenger();
  this->CreateSurface();
  this->PickPhysicalDevice();
  this->CreateLogicalDevice();
  std::cout << "LOG: Initalized Vulkan!\n";
}

void VulkanBackend::CreateInstance() {
  constexpr vk::ApplicationInfo appInfo{
      .pApplicationName = "RlClone",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "Revolution Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = vk::ApiVersion14};

  // Get the required layers
  std::vector<char const *> requiredLayers;
  if (enableValidationLayers) {
    requiredLayers.assign(validationLayers.begin(), validationLayers.end());
  }

  // Check if the required layers are supported by the Vulkan implementation.
  auto layerProperties = context.enumerateInstanceLayerProperties();
  auto unsupportedLayerIt = std::ranges::find_if(
      requiredLayers, [&layerProperties](auto const &requiredLayer) {
        return std::ranges::none_of(
            layerProperties, [requiredLayer](auto const &layerProperty) {
              return strcmp(layerProperty.layerName, requiredLayer) == 0;
            });
      });
  if (unsupportedLayerIt != requiredLayers.end()) {
    throw std::runtime_error("Required layer not supported: " +
                             std::string(*unsupportedLayerIt));
  }

  // Get the required extensions.
  auto requiredExtensions = getRequiredInstanceExtensions();

  // Check if the required extensions are supported by the Vulkan
  // implementation.
  auto extensionProperties = context.enumerateInstanceExtensionProperties();
  auto unsupportedPropertyIt = std::ranges::find_if(
      requiredExtensions,
      [&extensionProperties](auto const &requiredExtension) {
        return std::ranges::none_of(
            extensionProperties,
            [requiredExtension](auto const &extensionProperty) {
              return strcmp(extensionProperty.extensionName,
                            requiredExtension) == 0;
            });
      });
  if (unsupportedPropertyIt != requiredExtensions.end()) {
    throw std::runtime_error("Required extension not supported: " +
                             std::string(*unsupportedPropertyIt));
  }

  vk::InstanceCreateInfo createInfo{
      .pApplicationInfo = &appInfo,
      .enabledLayerCount = static_cast<uint32_t>(requiredLayers.size()),
      .ppEnabledLayerNames = requiredLayers.data(),
      .enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size()),
      .ppEnabledExtensionNames = requiredExtensions.data()};
  instance = vk::raii::Instance(context, createInfo);
}

void VulkanBackend::SetupDebugMessenger() {
  if (!enableValidationLayers)
    return;

  vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
  vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
      vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
      vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
      vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);
  vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT{
      .messageSeverity = severityFlags,
      .messageType = messageTypeFlags,
      .pfnUserCallback = &debugCallback};
  debugMessenger =
      instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
}

void VulkanBackend::PickPhysicalDevice() {
  std::vector<vk::raii::PhysicalDevice> physicalDevices =
      instance.enumeratePhysicalDevices();
  auto const devIter =
      std::ranges::find_if(physicalDevices, [&](auto const &physicalDevice) {
        return isDeviceSuitable(physicalDevice);
      });
  if (devIter == physicalDevices.end()) {
    throw std::runtime_error("failed to find a suitable GPU!");
  }
  physicalDevice = *devIter;
}

void VulkanBackend::CreateLogicalDevice() {
  // find the index of the first queue family that supports graphics
  std::vector<vk::QueueFamilyProperties> queueFamilyProperties =
      physicalDevice.getQueueFamilyProperties();

  // get the first index into queueFamilyProperties which supports graphics
  auto graphicsQueueFamilyProperty =
      std::ranges::find_if(queueFamilyProperties, [](auto const &qfp) {
        return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) !=
               static_cast<vk::QueueFlags>(0);
      });
  assert(graphicsQueueFamilyProperty != queueFamilyProperties.end() &&
         "No graphics queue family found!");

  auto graphicsIndex = static_cast<uint32_t>(std::distance(
      queueFamilyProperties.begin(), graphicsQueueFamilyProperty));

  // query for Vulkan 1.3 features
  vk::StructureChain<vk::PhysicalDeviceFeatures2,
                     vk::PhysicalDeviceVulkan13Features,
                     vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>
      featureChain = {
          {},                         // vk::PhysicalDeviceFeatures2
          {.dynamicRendering = true}, // vk::PhysicalDeviceVulkan13Features
          {.extendedDynamicState =
               true} // vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT
      };

  // create a Device
  float queuePriority = 0.5f;
  vk::DeviceQueueCreateInfo deviceQueueCreateInfo{
      .queueFamilyIndex = graphicsIndex,
      .queueCount = 1,
      .pQueuePriorities = &queuePriority};
  vk::DeviceCreateInfo deviceCreateInfo{
      .pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &deviceQueueCreateInfo,
      .enabledExtensionCount =
          static_cast<uint32_t>(requiredDeviceExtension.size()),
      .ppEnabledExtensionNames = requiredDeviceExtension.data()};

  device = vk::raii::Device(physicalDevice, deviceCreateInfo);
  graphicsQueue = vk::raii::Queue(device, graphicsIndex, 0);
};

void VulkanBackend::CreateSurface() {
  VkSurfaceKHR _surface;
  if (glfwCreateWindowSurface(*instance, this->MainWindow, nullptr,
                              &_surface) != 0) {
    throw std::runtime_error("failed to create window surface!");
  }
  surface = vk::raii::SurfaceKHR(instance, _surface);
}

std::vector<const char *> VulkanBackend::getRequiredInstanceExtensions() {
  uint32_t glfwExtensionCount = 0;
  auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
  if (enableValidationLayers) {
    extensions.push_back(vk::EXTDebugUtilsExtensionName);
  }

  return extensions;
}

VKAPI_ATTR vk::Bool32 VKAPI_CALL VulkanBackend::debugCallback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
    vk::DebugUtilsMessageTypeFlagsEXT type,
    const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData, void *) {
  if (severity == vk::DebugUtilsMessageSeverityFlagBitsEXT::eError ||
      severity == vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
    std::cerr << "validation layer: type " << to_string(type)
              << " msg: " << pCallbackData->pMessage << std::endl;
  }

  return vk::False;
}

bool VulkanBackend::isDeviceSuitable(
    vk::raii::PhysicalDevice const &physicalDevice) {
  // Check if the physicalDevice supports the Vulkan 1.3 API version
  bool supportsVulkan1_3 =
      physicalDevice.getProperties().apiVersion >= VK_API_VERSION_1_3;

  // Check if any of the queue families support graphics operations
  auto queueFamilies = physicalDevice.getQueueFamilyProperties();
  bool supportsGraphics =
      std::ranges::any_of(queueFamilies, [](auto const &qfp) {
        return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics);
      });

  // Check if all required physicalDevice extensions are available
  auto availableDeviceExtensions =
      physicalDevice.enumerateDeviceExtensionProperties();
  bool supportsAllRequiredExtensions = std::ranges::all_of(
      requiredDeviceExtension,
      [&availableDeviceExtensions](auto const &requiredDeviceExtension) {
        return std::ranges::any_of(
            availableDeviceExtensions,
            [requiredDeviceExtension](auto const &availableDeviceExtension) {
              return strcmp(availableDeviceExtension.extensionName,
                            requiredDeviceExtension) == 0;
            });
      });

  // Check if the physicalDevice supports the required features
  auto features = physicalDevice.template getFeatures2<
      vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan13Features,
      vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();
  bool supportsRequiredFeatures =
      features.template get<vk::PhysicalDeviceVulkan13Features>()
          .dynamicRendering &&
      features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>()
          .extendedDynamicState;

  // Return true if the physicalDevice meets all the criteria
  return supportsVulkan1_3 && supportsGraphics &&
         supportsAllRequiredExtensions && supportsRequiredFeatures;
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
