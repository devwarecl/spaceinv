#pragma once

#ifndef __textureloader__
#define __textureloader__

#include <list>
#include <string>
#include "gl3/Texture.hpp"

class TextureLoader {
public:
    TextureLoader();

    ~TextureLoader();

    void addPath(const std::string &path);

    gl3::TexturePtr loadTexture(const std::string &file);

protected:
    gl3::TexturePtr doLoadTexture(const std::string &file);

private:
    std::list<std::string> m_paths;
};

#endif 
