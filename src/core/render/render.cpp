#include <render.hpp>

core::Renderer::Renderer() {}
core::Renderer::~Renderer() {}

void core::Renderer::Init() {
  this->BackendRenderer.InitWindowSystem();
  this->BackendRenderer.HintWindow();
}

void core::Renderer::CreateWindow(unsigned int width, unsigned int height, const char *title) {
  this->BackendRenderer.CreateWindow(width, height, title);
}

void core::Renderer::InitSpecial(){
 this->BackendRenderer.InitSpecial();
}
 
bool core::Renderer::WindowShouldClose() {
  return this->BackendRenderer.WindowShouldClose();
}

void core::Renderer::PollEvents() {
  this->BackendRenderer.WindowSystemPollEvents();
}

void core::Renderer::BeginDrawing() {
  this->BackendRenderer.BeginDrawing();
}

void core::Renderer::EndDrawing() {
  this->BackendRenderer.EndDrawing();
}

void core::Renderer::CloseWindow() {
  this->BackendRenderer.CloseWindow();
}

void core::Renderer::CleanUp() {
  this->BackendRenderer.CleanUpWindowSystem();
}
