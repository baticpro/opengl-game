//
// Created by batraz jioty on 28.03.2022.
//

#include <iostream>
#include "ShaderManager.h"

Renderer::ShaderManager::ShaderManager(const std::string &vertexStr, const std::string &fragmentStr) {
    GLuint vertexId;
    if (!createShader(vertexStr, GL_VERTEX_SHADER, vertexId)) {
        return;
    }

    GLuint fragmentId;
    if (!createShader(fragmentStr, GL_FRAGMENT_SHADER, fragmentId)) {
        return;
    }

    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexId);
    glAttachShader(m_programId, fragmentId);
    glLinkProgram(m_programId);

    GLint status;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &status);
    if (!status) {
        GLchar info[1024];
        glGetProgramInfoLog(m_programId, 1024, nullptr, info);

        std::cerr << "program compile error [shaderID] -> " << m_programId << "\n" << info << std::endl;
        return;
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    m_isReady = true;
}

bool Renderer::ShaderManager::createShader(const std::string &shaderStr, const GLenum shaderType, GLuint &shaderId) {
    shaderId = glCreateShader(shaderType);
    const char *pCode = shaderStr.c_str();
    glShaderSource(shaderId, 1, &pCode, nullptr);
    glCompileShader(shaderId);

    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLchar info[1024];
        glGetShaderInfoLog(shaderId, 1024, nullptr, info);

        std::cerr << "shader compile error: [shaderID] -> " << shaderId << "\n" << info << std::endl;
        return false;
    }

    return true;
}

Renderer::ShaderManager::~ShaderManager() {
    glDeleteProgram(m_programId);
}

void Renderer::ShaderManager::use() const {
    glUseProgram(m_programId);
}
