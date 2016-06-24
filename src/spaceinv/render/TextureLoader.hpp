#pragma once

#ifndef __textureloader__
#define __textureloader__

#include <list>
#include <string>

#include "xe/FileLocator.hpp"
#include "gl3/TextureGL.hpp"

class TextureLoader {
public:
    explicit TextureLoader(xe::FileLocator *locator=nullptr);

    ~TextureLoader();

	void setLocator(xe::FileLocator *locator) {
		m_locator = locator;
	}

	xe::FileLocator *getLocator() {
		return m_locator;
	}

    gl3::TexturePtr loadTexture(const std::string &file);

protected:
    gl3::TexturePtr doLoadTexture(const std::string &file);

private:
	xe::FileLocator *m_locator = nullptr;
};

#endif 
