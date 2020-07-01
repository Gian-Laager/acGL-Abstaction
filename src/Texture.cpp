#include "Texture.h"

using namespace glAbs;

unsigned int Texture::boundId = 0;

Texture::Texture(const char* path, GLenum type) : filePath(path), type(type)
{
    stbi_set_flip_vertically_on_load(1);
    buffer = stbi_load(filePath, &width, &height, &bpp, 4);
    glCall(glGenTextures(1, &id));
    bind();

    glCall(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glCall(glTexImage2D(type, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
    unbind();

    if (buffer)
        stbi_image_free(buffer);
}

int Texture::getHeight()
{
    return height;
}

int Texture::getWidth()
{
    return width;
}

void Texture::bind(unsigned int slot) const
{
    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(type, id));
}

void Texture::unbind() const
{
    if (Texture::boundId == id)
    {
        glCall(glBindTexture(type, 0));
        Texture::boundId = 0;
    }
}

Texture::~Texture()
{
    glCall(glDeleteTextures(1, &id));
}

Texture::Texture(const char* path) : filePath(path), type(GL_TEXTURE_2D)
{
    stbi_set_flip_vertically_on_load(1);
    buffer = stbi_load(filePath, &width, &height, &bpp, 4);
    glCall(glGenTextures(1, &id));
    bind();

    glCall(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glCall(glTexImage2D(type, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
    unbind();

    if (buffer)
        stbi_image_free(buffer);
}

void Texture::bind() const
{
    if (Texture::boundId != id)
    {
        glCall(glActiveTexture(GL_TEXTURE0));
        glCall(glBindTexture(type, id));
        Texture::boundId = id;
    }
}
