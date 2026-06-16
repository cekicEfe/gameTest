#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

// For managing assets and shaders
#include <map>

// For uint32_last_t -> to index assets and shaders
#include <cstdint>

// For the std::numeric_limits<std::uint32_t>::max()
#include <limits>

// For optional data type
#include <optional>

// For exceptions
#include <exception>
#include <stdexcept>

// For error logging
#include <iostream>

// For asset hashing
#include <entt/entt.hpp>

#include <raylib.h>

#include <string>


// This will be a problem if we want to port this shi to the Android and web
#define GLSL_SHADER_VERSION 330


namespace RlClone {


// Using map is problematic change it to vector in the future
using ModelMap = std::map<std::uint32_t, Model>;
using TextureMap = std::map<std::uint32_t, Texture2D>;
using ShaderMap = std::map<std::uint32_t, Shader>;


using ModelAnimationCount = uint32_t;
using ModelAnimationsMap = std::map<std::uint32_t, std::pair<ModelAnimation*, ModelAnimationCount>>;


class AssetManager final {
private:
    ModelMap models;
    TextureMap textures;
    ModelAnimationsMap animations;
    ShaderMap shaders;
public:
    AssetManager();
    ~AssetManager();


    std::optional<std::uint32_t> PutModel(const std::string asset_name);
    std::optional<std::reference_wrapper<Model>> GetModel(std::uint32_t id);
    void DeleteModel(std::uint32_t model_id);


    std::optional<std::uint32_t> PutTexture(const std::string asset_name);
    std::optional<std::reference_wrapper<Texture2D>> GetTexture(std::uint32_t id);
    void DeleteTexture(std::uint32_t texture_id);


    std::optional<std::uint32_t> PutModelAnimation(const std::string asset_name);
    std::optional<std::reference_wrapper<std::pair<ModelAnimation*, RlClone::ModelAnimationCount>>>
    GetModelAnimation(std::uint32_t id);
    void DeleteModelAnimation(std::uint32_t model_animation_id);


    std::optional<std::uint32_t>
    PutShader(const std::string vert_shader_name = "", const std::string frag_shader_name = "");
    std::optional<std::reference_wrapper<Shader>> GetShader(std::uint32_t id);
    void DeleteShader(std::uint32_t shader_id);
};


} // namespace RlClone

#endif
