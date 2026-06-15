#include "AssetManager.hpp"


RlClone::AssetManager::AssetManager() {}


RlClone::AssetManager::~AssetManager() {

  for (auto& [model_id, model] : this->models) {
    UnloadModel(model);
  }

  for (auto& [texture_id, texture] : this->textures) {
    UnloadTexture(texture);
  }

  for (auto& [animation_id, model_anim] : this->animations) {
    UnloadModelAnimations(model_anim.first, model_anim.second);
  }  

  for (auto& [shader_id, shader] : this->shaders) {
    UnloadShader(shader);
  }  
    
}


std::uint32_t RlClone::AssetManager::PutModel(Model&& model) {
    if (this->last_model_index == std::numeric_limits<std::uint32_t>::max()) {
        throw std::runtime_error(
            "Maximum model count reached."); // Might remove this later this is very problematic
    }
    else {
        this->models[++last_model_index] = model;
        return last_model_index;
    }
}


std::optional<std::reference_wrapper<Model>>
RlClone::AssetManager::GetModel(std::uint32_t model_id) {
    if (auto iterator = this->models.find(model_id); iterator != this->models.end()) {
        return std::ref(iterator->second);
    }
    else {
        return std::nullopt;
    }
}


void RlClone::AssetManager::DeleteModel(std::uint32_t model_id) {
    if (auto iterator = this->models.find(model_id); iterator != this->models.end()) {
        UnloadModel(
            std::move(
                iterator->second)); // We take the ownership of the model first THEN unload it;
        this->models.erase(iterator);
    }
    else {
        std::cout << "[Warning]: Tried to free model that does not exists in AssetManager"
                  << std::endl;
    }
}


std::uint32_t RlClone::AssetManager::PutTexture(Texture2D&& texture) {
    if (this->last_texture_index == std::numeric_limits<std::uint32_t>::max()) {
        throw std::runtime_error(
            "Maximum texture count reached."); // Might remove this later this is very problematic
    }
    else {
        this->textures[++this->last_texture_index] = texture;
        return this->last_texture_index;
    }
}


std::optional<std::reference_wrapper<Texture2D>>
RlClone::AssetManager::GetTexture(std::uint32_t texture_id) {
    if (auto iterator = this->textures.find(texture_id); iterator != this->textures.end()) {
        return std::ref(iterator->second);
    }
    else {
        return std::nullopt;
    }
}


void RlClone::AssetManager::DeleteTexture(std::uint32_t texture_id) {
    if (auto iterator = this->textures.find(texture_id); iterator != this->textures.end()) {
        UnloadTexture(std::move(iterator->second));
        this->textures.erase(iterator);
    }
    else {
        std::cout << "[Warning]:Deleted texture not found in AssetManager" << std::endl;
    }
}


std::uint32_t RlClone::AssetManager::PutModelAnimation(
    std::pair<ModelAnimation*, RlClone::ModelAnimationCount>&& animation) {
    if (this->last_animation_index == std::numeric_limits<std::uint32_t>::max()) {
        throw std::runtime_error(
            "Maximum animation count reached"); // Might remove this later this is very problematic
    }
    else {
        this->animations[++last_animation_index] = animation;
        return last_animation_index;
    }
}


std::optional<
    std::reference_wrapper<std::pair<ModelAnimation*, RlClone::ModelAnimationCount>>>
RlClone::AssetManager::GetModelAnimation(std::uint32_t model_animation_id) {
    if (auto iterator = this->animations.find(model_animation_id);
        iterator != this->animations.end()) {
        return std::ref(iterator->second);
    }
    else {
        return std::nullopt;
    }
}


void RlClone::AssetManager::DeleteModelAnimation(std::uint32_t model_animation_id) {
    if (auto iterator = this->animations.find(model_animation_id);
        iterator != this->animations.end()) {
        auto model_anim = std::move(iterator->second);
        UnloadModelAnimations(model_anim.first, model_anim.second);
        this->animations.erase(iterator);
    }
    else {
        std::cout << "[Warning]:Deleted model animation not found in AssetManager" << std::endl;
    }
}


std::uint32_t RlClone::AssetManager::PutShader(Shader&& shader) {
    if (this->last_shader_index == std::numeric_limits<std::uint32_t>::max()) {
        throw std::runtime_error(
            "Maximum shader count reached."); // Might remove this later this is very problematic
    }
    else {
        this->shaders[++last_shader_index] = shader;
        return last_shader_index;
    }
}


std::optional<std::reference_wrapper<Shader>>
RlClone::AssetManager::GetShader(std::uint32_t shader_id) {
    if (auto iterator = this->shaders.find(shader_id); iterator != this->shaders.end()) {
        return std::ref(iterator->second);
    }
    else {
        return std::nullopt;
    }
}


void RlClone::AssetManager::DeleteShader(std::uint32_t shader_id) {
    if (auto iterator = this->shaders.find(shader_id); iterator != this->shaders.end()) {
        UnloadShader(
            std::move(
                iterator->second)); // We take the ownership of the model first THEN unload it;
        this->shaders.erase(iterator);
    }
    else {
        std::cout << "[Warning]: Tried to free shader that does not exists in AssetManager"
                  << std::endl;
    }
}
