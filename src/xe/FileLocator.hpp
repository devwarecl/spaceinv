
#pragma once

#ifndef __xe_filelocator__
#define __xe_filelocator__

#include <list>
#include <string>

namespace xe {
	class FileLocator {
	public:
		void addPath(const std::string &path) {
			m_paths.push_back(path);
		}

		std::string locate(const std::string &name);

	private:
		std::list<std::string> m_paths;
	};
}

#endif 
