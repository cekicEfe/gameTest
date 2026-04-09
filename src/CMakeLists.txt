add_executable(RevEngine main.cpp)

add_executable(RevEngine
  main.cpp
  game/game.hpp
  game/game.cpp
  app/app.cpp  
  app/app.hpp
  core/render/vulkan_backend.cpp
  core/render/vulkan_backend.hpp
  core/render/render.hpp
  core/render/render.cpp
  core/render/backend_interface.hpp
)
