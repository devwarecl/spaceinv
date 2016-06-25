
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

xe::gfx::gl3::TexturePtr TextureLoader::loadTexture(const std::string &file) {
    xe::gfx::gl3::TexturePtr texture;

	std::string location = file;

	if (m_locator) {
		std::string location = m_locator->locate(file);
		texture = this->doLoadTexture(location);
	}

    return texture;
}

xe::gfx::gl3::TexturePtr TextureLoader::doLoadTexture(const std::string &file) {
    FIBITMAP *bitmap = ::FreeImage_Load(FIF_BMP, file.c_str());

    if (!bitmap) {
        std::cerr << "No se pudo cargar textura '" << file << "'." << std::endl;

        return xe::gfx::gl3::TexturePtr();
    }

    bitmap = FreeImage_ConvertTo24Bits(bitmap);

    auto width = ::FreeImage_GetWidth(bitmap);
    auto height = ::FreeImage_GetHeight(bitmap);
    auto bpp = ::FreeImage_GetBPP(bitmap);
    void* data = ::FreeImage_GetBits(bitmap);
        
    auto texture = std::make_unique<xe::gfx::gl3::TextureGL>(width, height, data, GL_BGR);

    ::FreeImage_Unload(bitmap);

    return texture;
}
