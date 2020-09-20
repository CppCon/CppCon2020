#ifndef DEMO_SVGDRAWING_H
#define DEMO_SVGDRAWING_H

#include <string>

class SVGDrawing
{
public:
    // File names are in resources sub-directory, relative to the
    // location of this source code.
    explicit SVGDrawing( const std::string& source_svg_file );

    // Return the SVG text from the file
    std::string content() const;

private:
    std::string m_source_svg_file;
};

SVGDrawing createDrawing( const std::string& source_svg_file );

#endif //DEMO_SVGDRAWING_H
