//
// Created by batraz jioty on 05.04.2022.
//

#include "Texture2D.h"

using namespace Renderer;

Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char *data, const unsigned int channels,
                     const GLenum filter, const GLenum wrapMode) : m_width(width), m_height(height) {

    m_mode = channels == 4 ? GL_RGBA : GL_RGB;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_id);
}
