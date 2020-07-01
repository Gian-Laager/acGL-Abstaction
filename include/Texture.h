#pragma once

#include "pch.h"

namespace glAbs
{
    class Texture
    {
    private:
        const char* filePath;
        GLenum type;
        unsigned int id;
        unsigned char* buffer = nullptr;
        int width, height, bpp;
    public:
        static unsigned int boundId;

        Texture(const char* path, GLenum type);

        Texture(const char* path);

        ~Texture();

        int getHeight();

        int getWidth();

        void bind(GLenum slot) const;

        void bind() const;

        void unbind() const;
    };
}