#pragma once

#ifndef __meshloader__
#define __meshloader__

#include "Mesh.hpp"
#include "TextureLoader.hpp"

#include "xe/FileLocator.hpp"

class MeshLoader {
public:
	explicit MeshLoader(xe::FileLocator *locator=nullptr) {
		this->setLocator(locator);
	}

	~MeshLoader() {}

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

	const TextureLoader *getTextureLoader() const {
		return m_textureLoader;
	}

	std::vector<Mesh> createMeshSet(const std::string &path, const gl3::MeshFormat &format);

private:
	TextureLoader *m_textureLoader = nullptr;
	xe::FileLocator *m_locator = nullptr;
};

#endif
