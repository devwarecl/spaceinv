#pragma once

#ifndef __meshloader__
#define __meshloader__

#include "Mesh.hpp"
#include "TextureLoader.hpp"

class MeshLoader {
public:
	MeshLoader() {}
	~MeshLoader() {}

	void setTextureLoader(TextureLoader *textureLoader) {
		m_textureLoader = textureLoader;
	}

	TextureLoader *getTextureLoader() {
		return m_textureLoader;
	}

	const TextureLoader *getTextureLoader() const {
		return m_textureLoader;
	}

	std::vector<Mesh> createMeshSet(const std::string &path, const gl3::SubsetFormat &format);

private:
	TextureLoader *m_textureLoader = nullptr;
};

#endif
