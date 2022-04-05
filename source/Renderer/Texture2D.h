//
// Created by batraz jioty on 05.04.2022.
//

#ifndef OPENGL_GAME_TEXTURE2D_H
#define OPENGL_GAME_TEXTURE2D_H

#define DEFAULT_CHANNELS 4
#define DEFAULT_FILTER GL_LINEAR
#define DEFAULT_WRAP_MODE GL_CLAMP_TO_EDGE

#include <glad/glad.h>
#include <string>

namespace Renderer {
    class Texture2D {
    public:
        Texture2D() = delete;

        Texture2D(
                const GLuint width,
                const GLuint height,
                const unsigned char *data,
                const unsigned int channels = DEFAULT_CHANNELS,
                const GLenum filter = DEFAULT_FILTER,
                const GLenum wrapMode = DEFAULT_WRAP_MODE
        );

        Texture2D(const Texture2D &) = delete;

        Texture2D &operator=(const Texture2D &) = delete;


        ~Texture2D();

    private:
        GLuint m_id;
        GLenum m_mode;

        unsigned int m_width;
        unsigned int m_height;
    };
}

#endif //OPENGL_GAME_TEXTURE2D_H
