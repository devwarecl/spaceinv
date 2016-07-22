#pragma once

#ifndef __textureloader__
#define __textureloader__

#include <list>
#include <string>
#include <map>

#include "xe/FileLocator.hpp"
#include "xe/gfx/Device.hpp"
#include "xe/gfx/Texture.hpp"

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

    void setDevice(xe::gfx::Device *device) {
        m_device = device;
    }

    xe::gfx::Device* getDevice() {
        return m_device;
    }

    const xe::gfx::Device* getDevice() const {
        return m_device;
    }

    xe::gfx::Texture* loadTexture(const std::string &file);

protected:
    xe::gfx::TexturePtr doLoadTexture(const std::string &file);

private:
    xe::FileLocator *m_locator = nullptr;
    xe::gfx::Device *m_device = nullptr;
    std::map<std::string, xe::gfx::TexturePtr> m_textures;
};

#endif 
