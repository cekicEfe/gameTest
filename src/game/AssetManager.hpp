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


#include <raylib.h>


namespace RlClone {


// Using map is problematic change it to vector in the future 
using ModelMap = std::map<std::uint32_t, Model>;
using TextureMap = std::map<std::uint32_t, Texture2D>;
using ShaderMap = std::map<std::uint32_t, Shader>;


using ModelAnimationCount = uint32_t;
using ModelAnimationsMap =
    std::map<std::uint32_t, std::pair<ModelAnimation*, ModelAnimationCount>>;


class AssetManager final {
private:
    ModelMap models;
    std::uint32_t last_model_index = 0;


    TextureMap textures;
    std::uint32_t last_texture_index = 0;


    ModelAnimationsMap animations;
    std::uint32_t last_animation_index = 0;


    ShaderMap shaders;
    std::uint32_t last_shader_index = 0;
public:
    AssetManager();
    ~AssetManager();


    std::uint32_t PutModel(Model&& model);
    std::optional<std::reference_wrapper<Model>> GetModel(std::uint32_t id);
    void DeleteModel(std::uint32_t model_id);


    std::uint32_t PutTexture(Texture2D&& texture);
    std::optional<std::reference_wrapper<Texture2D>> GetTexture(std::uint32_t id);
    void DeleteTexture(std::uint32_t model_id);


    std::uint32_t
    PutModelAnimation(std::pair<ModelAnimation*, RlClone::ModelAnimationCount>&& animation);
    std::optional<
        std::reference_wrapper<std::pair<ModelAnimation*, RlClone::ModelAnimationCount>>>
    GetModelAnimation(std::uint32_t id);
    void DeleteModelAnimation(std::uint32_t model_animation_id);


    std::uint32_t PutShader(Shader&& shader);
    std::optional<std::reference_wrapper<Shader>> GetShader(std::uint32_t id);
    void DeleteShader(std::uint32_t shader_id);

  
};


} // namespace RlClone

#endif
