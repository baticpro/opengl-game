//
// Created by batraz jioty on 30.03.2022.
//

#include "AssetsManager.h"
#include "../Renderer/ShaderManager.h"

#include <utility>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "../../../vendor/stb_image/stb_image.h"

AssetsManager::AssetsManager(const std::string &absolutePath) {
    auto pos = absolutePath.find_last_of('/');
    m_path = absolutePath.substr(0, pos);
}

std::string AssetsManager::getFileContent(const std::string &relativePath) {
    std::ifstream f;

    f.open((m_path + "/assets/" + relativePath).c_str());
    if (f.is_open()) {
        std::stringstream stringstream;
        stringstream << f.rdbuf();
        return stringstream.str();
    }

    return "";
}

std::shared_ptr<Renderer::ShaderManager> AssetsManager::loadShader(std::string name) {
    std::string vertexPath = "/shaders/" + name + "Vertex.txt";
    std::string fragmentPath = "/shaders/" + name + "Fragment.txt";

    auto vertexStr = getFileContent(vertexPath);
    auto fragmentStr = getFileContent(fragmentPath);

    auto shader = std::make_shared<Renderer::ShaderManager>(vertexStr, fragmentStr);
    m_shaders.emplace(name, shader);

    return shader;
}

void AssetsManager::loadTexture(std::string name) {
    int channels = 0, width = 0, height = 0;
    stbi_set_flip_vertically_on_load(true);
    std::string pathName = m_path + "/assets/textures/" + name;
    auto pixels = stbi_load(pathName.c_str(), &width, &height, &channels, 0);

    stbi_image_free(pixels);
}
