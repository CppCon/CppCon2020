#ifndef DEMO_STRINGUTILITIES_H
#define DEMO_STRINGUTILITIES_H

#include <string>

namespace StringUtilities
{
    std::string replaceAll( std::string inText,
                            const std::string& find,
                            const std::string& replaceWith );
}

#endif //DEMO_STRINGUTILITIES_H
