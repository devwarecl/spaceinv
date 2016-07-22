#pragma once

#ifndef __meshloader__
#define __meshloader__

#include "../Model.hpp"
#include "TextureLoader.hpp"

#include "xe/FileLocator.hpp"
#include "xe/gfx/Device.hpp"

#include <map>

class ModelLoader {
public:
    ModelLoader(xe::FileLocator *locator=nullptr, xe::gfx::Device *device=nullptr) {
        this->setLocator(locator);
    }

    ~ModelLoader() {}

    void setTextureLoader(TextureLoader *textureLoader) {
        m_textureLoader = textureLoader;
    }

    void setLocator(xe::FileLocator *locator) {
        m_locator = locator;
    }

    xe::FileLocator* getLocator() {
        return m_locator;
    }

    TextureLoader *getTextureLoader() {
        return m_textureLoader;
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

    const TextureLoader *getTextureLoader() const {
        return m_textureLoader;
    }

    Model* getModel(const std::string &model, xe::gfx::UniformFormat *materialFormat=nullptr, const xe::gfx::MeshFormat *format=nullptr);

protected:
    ModelPtr createModel(const std::string &name, xe::gfx::UniformFormat *materialFormat, const xe::gfx::MeshFormat &format);

private:
    TextureLoader *m_textureLoader = nullptr;
    xe::FileLocator *m_locator = nullptr;
    xe::gfx::Device *m_device = nullptr;
    std::map<std::string, ModelPtr> m_models;
};

#endif
