
#include <iostream>
#include "TextureLoader.hpp"
#include "FreeImage.h"

TextureLoader::TextureLoader(xe::FileLocator *locator) {
    this->setLocator(locator);
    ::FreeImage_Initialise();
}

TextureLoader::~TextureLoader() {
    ::FreeImage_DeInitialise();
}

xe::gfx::Texture* TextureLoader::loadTexture(const std::string &file) {
    xe::gfx::TexturePtr texture;

    std::string location = file;

    if (m_locator) {
        location = m_locator->locate(file);
    }

    if (m_textures.find(location) == m_textures.end()) {
        texture = this->doLoadTexture(location);
        m_textures[location] = std::move(texture);
    }

    return m_textures[location].get();
}

xe::gfx::TexturePtr TextureLoader::doLoadTexture(const std::string &file) {
    FIBITMAP *bitmap = ::FreeImage_Load(FIF_BMP, file.c_str());

    if (!bitmap) {
        std::cerr << "No se pudo cargar textura '" << file << "'." << std::endl;

        return xe::gfx::TexturePtr();
    }

    bitmap = FreeImage_ConvertTo24Bits(bitmap);

    xe::gfx::TextureDesc textureDesc;
    textureDesc.type = xe::gfx::TextureType::Tex2D;
    textureDesc.width = ::FreeImage_GetWidth(bitmap);
    textureDesc.height = ::FreeImage_GetHeight(bitmap);
    textureDesc.format = xe::gfx::PixelFormat::R8G8B8;

    void* data = ::FreeImage_GetBits(bitmap);
    
    auto texture = m_device->createTexture(textureDesc, xe::gfx::PixelFormat::B8G8R8, xe::DataType::UInt8, data);

    ::FreeImage_Unload(bitmap);

    return texture;
}
