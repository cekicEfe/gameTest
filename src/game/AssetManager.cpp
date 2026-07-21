#include "AssetManager.hpp"

const std::string RlClone::AssetManager::DEFAULT_CUBE_MODEL =
    "resources/default_assets/default_models/default_cube/DefaultCube.obj";
const std::string RlClone::AssetManager::DEFAULT_CUBE_TEXTURE =
    "resources/default_assets/default_models/default_cube/DefaultCubeTexture.png";

const std::string RlClone::AssetManager::DEFAULT_SPHERE_MODEL =
    "resources/default_assets/default_models/default_sphere/DefaultSphere.obj";
const std::string RlClone::AssetManager::DEFAULT_SPHERE_TEXTURE =
    "resources/default_assets/default_models/default_sphere/DefaultSphereTexture.png";

const std::string RlClone::AssetManager::DEFAULT_TEXTURE =
    "resources/default_assets/default_models/DefaultTexture.png";
const std::string RlClone::AssetManager::DEFAULT_VERT_SHADER =
    "resources/default_assets/default_shader/DefaultShader.vert";
const std::string RlClone::AssetManager::DEFAULT_FRAG_SHADER =
    "resources/default_assets/default_shader/DefaultShader.frag";


RlClone::AssetManager::AssetManager() {
    try {
        *this->PutModel(RlClone::AssetManager::DEFAULT_CUBE_MODEL);
        *this->PutTexture(RlClone::AssetManager::DEFAULT_CUBE_TEXTURE);

        *this->PutModel(RlClone::AssetManager::DEFAULT_SPHERE_MODEL);
        *this->PutTexture(RlClone::AssetManager::DEFAULT_SPHERE_TEXTURE);

        *this->PutTexture(RlClone::AssetManager::DEFAULT_TEXTURE);
        *this->PutShader(
            RlClone::AssetManager::DEFAULT_VERT_SHADER,
            RlClone::AssetManager::DEFAULT_FRAG_SHADER);
    } catch (...) {
        throw std::runtime_error("[ERROR]: Could not initialize all of the default assets");
    }
}


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


std::optional<std::uint32_t> RlClone::AssetManager::PutModel(const std::string asset_name) {
    try {
        auto string_hash = entt::hashed_string(asset_name.data()).value();

        if (this->models.find(string_hash) != this->models.end()) {
            // We already have the asset
            return string_hash;
        }
        else {
            // We don't have the asset
            Model model = LoadModel(asset_name.data());
            this->models[string_hash] = std::move(model);
            return string_hash;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
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


std::optional<std::reference_wrapper<Model>>
RlClone::AssetManager::GetModel(const std::string asset_name) {
    std::uint32_t model_id = entt::hashed_string(asset_name.data()).value();
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


std::optional<std::uint32_t> RlClone::AssetManager::PutTexture(const std::string asset_name) {
    try {
        auto string_hash = entt::hashed_string(asset_name.data()).value();

        if (this->textures.find(string_hash) != this->textures.end()) {
            // We already have the asset
            return string_hash;
        }
        else {
            // We don't have the asset
            Texture2D texture = LoadTexture(asset_name.data());
            this->textures[string_hash] = std::move(texture);
            return string_hash;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
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


std::optional<std::reference_wrapper<Texture2D>>
RlClone::AssetManager::GetTexture(const std::string asset_name) {
    std::uint32_t texture_id = entt::hashed_string(asset_name.data()).value();
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


std::optional<std::uint32_t>
RlClone::AssetManager::PutModelAnimation(const std::string asset_name) {
    try {
        auto string_hash = entt::hashed_string(asset_name.data()).value();

        if (this->animations.find(string_hash) != this->animations.end()) {
            // We already have the asset
            return string_hash;
        }
        else {
            // We don't have the asset
            int animCount = 0;
            ModelAnimation* anims = LoadModelAnimations(asset_name.data(), &animCount);

            this->animations[string_hash] = std::make_pair(anims, animCount);
            return string_hash;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
    }
}


std::optional<std::reference_wrapper<std::pair<ModelAnimation*, RlClone::ModelAnimationCount>>>
RlClone::AssetManager::GetModelAnimation(std::uint32_t model_animation_id) {
    if (auto iterator = this->animations.find(model_animation_id);
        iterator != this->animations.end()) {
        return std::ref(iterator->second);
    }
    else {
        return std::nullopt;
    }
}


std::optional<std::reference_wrapper<std::pair<ModelAnimation*, RlClone::ModelAnimationCount>>>
RlClone::AssetManager::GetModelAnimation(const std::string asset_name) {
    std::uint32_t model_animation_id = entt::hashed_string(asset_name.data()).value();
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


std::optional<std::uint32_t> RlClone::AssetManager::PutShader(
    const std::string vert_shader_name, const std::string frag_shader_name) {
    try {
        auto string_hash =
            entt::hashed_string((vert_shader_name + frag_shader_name).data()).value();

        if (this->shaders.find(string_hash) != this->shaders.end()) {
            // We already have the asset
            return string_hash;
        }
        else {
            Shader shader = LoadShader(
                (vert_shader_name == RlClone::AssetManager::DEFAULT_VERT_SHADER
                     ? RlClone::AssetManager::DEFAULT_VERT_SHADER.data()
                     : vert_shader_name.data()),
                (frag_shader_name == RlClone::AssetManager::DEFAULT_FRAG_SHADER
                     ? RlClone::AssetManager::DEFAULT_FRAG_SHADER.data()
                     : frag_shader_name.data()));

            this->shaders[string_hash] = std::move(shader);
            return string_hash;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
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
