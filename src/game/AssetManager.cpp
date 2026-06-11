#include "AssetManager.hpp"


RlClone::AssetManager::AssetManager() {}


RlClone::AssetManager::~AssetManager() {}


std::uint32_t RlClone::AssetManager::PutModel(raylib::Model&& model) {
    if (this->model_count == std::numeric_limits<std::uint32_t>::max()) {
        throw std::runtime_error(
            "Maximum model count reached."); // Might remove this later this is very problematic
    }
    else {
        this->models[++model_count] = model;
        return model_count;
    }
}


std::optional<std::reference_wrapper<raylib::Model>>
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
        raylib::UnloadModel(
            std::move(
                iterator->second)); // We take the ownership of the model first THEN unload it;
        this->models.erase(iterator);
    }
    else {
        std::cout << "[Warning]: Tried to free model that does not exists in AssetManager"
                  << std::endl;
    }
}


std::uint32_t RlClone::AssetManager::PutTexture(raylib::Texture2D&& texture) {
    if (this->texture_count == std::numeric_limits<std::uint32_t>::max()) {
        throw std::runtime_error(
            "Maximum texture count reached."); // Might remove this later this is very problematic
    }
    else {
        this->textures[++this->texture_count] = texture;
        return this->texture_count;
    }
}


std::optional<std::reference_wrapper<raylib::Texture2D>>
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
        raylib::UnloadTexture(std::move(iterator->second));
        this->textures.erase(iterator);
    }
    else {
        std::cout << "[Warning]:Deleted texture not found in AssetManager" << std::endl;
    }
}


std::uint32_t RlClone::AssetManager::PutModelAnimation(std::pair<raylib::ModelAnimation*,RlClone::ModelAnimationCount> &&animation) {
    if (this->animation_count == std::numeric_limits<std::uint32_t>::max()) {
        throw std::runtime_error(
            "Maximum animation count reached"); // Might remove this later this is very problematic
    }
    else {
        this->animations[++animation_count] = animation;
        return animation_count;
    }
}


std::optional<
    std::reference_wrapper<std::pair<raylib::ModelAnimation*, RlClone::ModelAnimationCount>>>
RlClone::AssetManager::GetModelAnimation(std::uint32_t model_animation_id) {
  if(auto iterator = this->animations.find(model_animation_id); iterator != this->animations.end()){
    return std::ref(iterator->second);
  }
  else{
    return std::nullopt;
  }
}


void RlClone::AssetManager::DeleteModelAnimation(std::uint32_t model_animation_id) {
  if(auto iterator = this->animations.find(model_animation_id); iterator != this->animations.end()){
    auto model_anim = std::move(iterator->second); 
    raylib::UnloadModelAnimations(model_anim.first,model_anim.second);
    this->animations.erase(iterator);
  }
  else{
        std::cout << "[Warning]:Deleted model animation not found in AssetManager" << std::endl;   
  }
}
