#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <map>
#include <cstdint>
#include <limits>
#include <optional>
#include <exception>
#include <stdexcept>

#include <string>
#include <iostream>

#include <entt/entt.hpp>
#include <raylib.h>


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

    static const std::string DEFAULT_CUBE_MODEL;
    static const std::string DEFAULT_CUBE_TEXTURE;

    static const std::string DEFAULT_SPHERE_MODEL;
    static const std::string DEFAULT_SPHERE_TEXTURE;

    static const std::string DEFAULT_TEXTURE;
    static const std::string DEFAULT_VERT_SHADER;
    static const std::string DEFAULT_FRAG_SHADER;

    std::optional<std::uint32_t> PutModel(const std::string asset_name);
    std::optional<std::reference_wrapper<Model>> GetModel(std::uint32_t id);
    std::optional<std::reference_wrapper<Model>> GetModel(const std::string asset_name);
    void DeleteModel(std::uint32_t model_id);

    std::optional<std::uint32_t> PutTexture(const std::string asset_name);
    std::optional<std::reference_wrapper<Texture2D>> GetTexture(std::uint32_t id);
    std::optional<std::reference_wrapper<Texture2D>> GetTexture(const std::string asset_name);
    void DeleteTexture(std::uint32_t texture_id);

    std::optional<std::uint32_t> PutModelAnimation(const std::string asset_name);
    std::optional<std::reference_wrapper<std::pair<ModelAnimation*, RlClone::ModelAnimationCount>>>
    GetModelAnimation(std::uint32_t id);
    std::optional<std::reference_wrapper<std::pair<ModelAnimation*, RlClone::ModelAnimationCount>>>
    GetModelAnimation(const std::string asset_name);
    void DeleteModelAnimation(std::uint32_t model_animation_id);

    std::optional<std::uint32_t> PutShader(
        const std::string vert_shader_name = RlClone::AssetManager::DEFAULT_VERT_SHADER,
        const std::string frag_shader_name = RlClone::AssetManager::DEFAULT_FRAG_SHADER);
    std::optional<std::reference_wrapper<Shader>> GetShader(std::uint32_t id);
    void DeleteShader(std::uint32_t shader_id);
};

} // namespace RlClone

#endif
