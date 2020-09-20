#include "FileUtilities.h"

#include <fstream>
#include <sstream>

namespace FileUtilities
{
    std::string readFileThrowIfMissing( const std::string& filePath )
    {
        std::ifstream in( filePath.c_str(), std::ios_base::in );
        if ( !in )
        {
            throw std::runtime_error( "File does not exist: " +
                                      filePath );
        }
        std::stringstream written;
        written << in.rdbuf();
        in.close();

        std::string text = written.str();
        return text;
    }

    void writeToFile( const std::string& filePath,
                      const std::string& content )
    {
        std::ofstream out( filePath.c_str(),
                           std::ios::binary | std::ofstream::out );
        if ( !out )
        {
            throw std::runtime_error( "Unable to write file: " +
                                      filePath );
        }
        out << content;
    }
}
