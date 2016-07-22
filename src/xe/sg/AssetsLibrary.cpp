
#include "AssetsLibrary.hpp"

#include <map>

namespace xe { namespace sg {
    struct AssetLibrary::Private {
        std::map<std::string, BufferPtr> assets;
    };
    
    AssetLibrary::AssetLibrary() {
        this->impl = new AssetLibrary::Private();
    }

    AssetLibrary::~AssetLibrary() {
        delete this->impl;
    }

    void AssetLibrary::addAsset(const std::string &fileId, BufferPtr assetData) {
        this->impl->assets[fileId] = std::move(assetData);
    }

    Buffer* AssetLibrary::getAsset(const std::string &file) {
        return this->impl->assets[file].get();
    }

    const Buffer* AssetLibrary::getAsset(const std::string &file) const {
        return this->impl->assets[file].get();
    }
}}
