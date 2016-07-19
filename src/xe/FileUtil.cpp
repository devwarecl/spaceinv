
#include "FileUtil.hpp"

#include <fstream>
#include <stdexcept>

namespace xe {
    std::string FileUtil::loadTextFile(const std::string &file) {
        std::fstream fs;

        fs.open(file.c_str(), std::ios_base::in);
        if (!fs.is_open()) {
            throw std::runtime_error("Couldn't open file '" + file + "'");
        }

        std::string content;

        while (!fs.eof()) {
            std::string line;
            std::getline(fs, line);

            content += line + "\n";
        }

        return content;
    }
}
