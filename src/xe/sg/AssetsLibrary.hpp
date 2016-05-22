
#pragma once

#ifndef __xe_sg_assetlibrary__
#define __xe_sg_assetlibrary__

#include <string>
#include <memory>
#include "xe/Buffer.hpp"

namespace xe { namespace sg {

	class AssetLibrary {
	public:
		AssetLibrary();
		~AssetLibrary();

		void addAsset(const std::string &fileId, BufferPtr assetData);
		Buffer* getAsset(const std::string &fileId);
		const Buffer* getAsset(const std::string &fileId) const;

	private:
		struct Private;
		Private *impl = nullptr;
	};

	typedef std::unique_ptr<AssetLibrary> AssetLibraryPtr;
}}

#endif	// __EXENG_SCENEGRAPH_ASSETLIBRARY_HPP__
