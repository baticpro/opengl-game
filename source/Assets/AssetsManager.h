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
}

class AssetsManager {
public:
    AssetsManager(std::string path);
    ~AssetsManager() = default;

    AssetsManager(const AssetsManager&) = delete;
    AssetsManager(AssetsManager&&) = delete;
    AssetsManager& operator=(const AssetsManager&) = delete;
    AssetsManager& operator=(AssetsManager&&) = delete;

    std::shared_ptr<Renderer::ShaderManager> loadShader(std::string name);

private:
    typedef std::map<std::string, std::shared_ptr<Renderer::ShaderManager>> ShadersMap;
    ShadersMap m_shaders;
    std::string m_path;
};


#endif //OPENGL_GAME_ASSETSMANAGER_H
