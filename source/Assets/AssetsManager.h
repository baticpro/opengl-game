//
// Created by batraz jioty on 30.03.2022.
//

#include <string>
#include <memory>
#include <map>

#ifndef OPENGL_GAME_ASSETSMANAGER_H
#define OPENGL_GAME_ASSETSMANAGER_H

namespace Renderer {
    class ShaderManager;
    class Texture2D;
}

class AssetsManager {
public:
    AssetsManager(const std::string& path);
    ~AssetsManager() = default;

    AssetsManager(const AssetsManager&) = delete;
    AssetsManager(AssetsManager&&) = delete;
    AssetsManager& operator=(const AssetsManager&) = delete;
    AssetsManager& operator=(AssetsManager&&) = delete;

    std::shared_ptr<Renderer::ShaderManager> loadShader(std::string name);
    std::shared_ptr<Renderer::Texture2D> loadTexture(std::string name);
private:
    std::string getFileContent(const std::string& relativePath);

    typedef std::map<std::string, std::shared_ptr<Renderer::ShaderManager>> ShadersMap;
    ShadersMap m_shaders;

    typedef std::map<std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
    TexturesMap m_textures;

    std::string m_path;
};


#endif //OPENGL_GAME_ASSETSMANAGER_H
