
#include <iostream>
#include "TextureLoader.hpp"
#include "FreeImage.h"

TextureLoader::TextureLoader() {
    ::FreeImage_Initialise();
}

TextureLoader::~TextureLoader() {
    ::FreeImage_DeInitialise();
}

void TextureLoader::addPath(const std::string &path) {
    m_paths.push_back(path);
}

gl3::TexturePtr TextureLoader::loadTexture(const std::string &file) {
    gl3::TexturePtr texture;

    if (m_paths.size()) {
        for (const auto &path : m_paths) {

            std::string textureName = path + file;

            texture = this->doLoadTexture(textureName);

            if (texture) {
                break;
            }
        }
    } else {
        texture = this->doLoadTexture(file);
    }

    return texture;
}

gl3::TexturePtr TextureLoader::doLoadTexture(const std::string &file) {
    FIBITMAP *bitmap = ::FreeImage_Load(FIF_BMP, file.c_str());

    if (!bitmap) {
        std::cerr << "No se pudo cargar textura '" << file << "'." << std::endl;

        return gl3::TexturePtr();
    }

    bitmap = FreeImage_ConvertTo24Bits(bitmap);

    auto width = ::FreeImage_GetWidth(bitmap);
    auto height = ::FreeImage_GetHeight(bitmap);
    auto bpp = ::FreeImage_GetBPP(bitmap);
    void* data = ::FreeImage_GetBits(bitmap);
        
    auto texture = std::make_unique<gl3::Texture>(width, height, data, GL_BGR);

    ::FreeImage_Unload(bitmap);

    return texture;
}
