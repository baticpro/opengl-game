//
// Created by batraz jioty on 28.03.2022.
//

#include <glad/glad.h>
#include <string>

#ifndef OPENGL_GAME_SHADERMANAGER_H
#define OPENGL_GAME_SHADERMANAGER_H

namespace Renderer {
    class ShaderManager {
    public:
        ShaderManager(const std::string& vertexStr, const std::string& fragmentStr);
        ~ShaderManager();

        bool isReady() const {return m_isReady;  }
        void use() const;

    private:
        static bool createShader(const std::string& shaderStr, GLenum shaderType, GLuint& shaderId);

        bool m_isReady = false;
        GLuint m_programId = 0;
    };
}


#endif //OPENGL_GAME_SHADERMANAGER_H
