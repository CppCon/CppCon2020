#ifndef DEMO_FILEUTILITIES_H
#define DEMO_FILEUTILITIES_H

#include <string>

namespace FileUtilities
{
    std::string readFileThrowIfMissing( const std::string& filePath );

    void writeToFile( const std::string& filePath,
                      const std::string& content );
}

#endif //DEMO_FILEUTILITIES_H
