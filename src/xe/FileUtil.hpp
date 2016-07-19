
#ifndef __xe_fileutil_hpp__
#define __xe_fileutil_hpp__

#include <string>

namespace xe {
    class FileUtil {
    private:
        FileUtil() {}
        ~FileUtil() {}
        
    public:
        static std::string loadTextFile(const std::string &file);
    };
}

#endif
