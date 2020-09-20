#include "SVGReporter.h"

bool SVGReporter::report( std::string receivedSVGFile,
                          std::string approvedSVGFile ) const
{
    // received and approved are files in SVG format
    std::string receivedAsPNG = convertToPNG( receivedSVGFile );
    std::string approvedAsPNG = convertToPNG( approvedSVGFile );

    ApprovalTests::Mac::BeyondCompareReporter beyondCompareReporter;

    // First show the differences in the converted .png files:
    beyondCompareReporter.report( receivedAsPNG, approvedAsPNG );

    // Then show the text differences in .svg files,
    // in the default reporter:
    return ApprovalTests::DiffReporter().report( receivedSVGFile,
                                                 approvedSVGFile );
}

std::string SVGReporter::convertToPNG( std::string SVGFile ) const
{
    std::filesystem::path inputPath( SVGFile );
    std::string extension = inputPath.extension();
    auto outputPath = inputPath;
    outputPath.replace_extension( "png" );
    if ( inputPath != outputPath )
    {
        auto path =
            "/Applications/Inkscape.app/Contents/MacOS/inkscape";
        auto arguments =
            "--export-overwrite --export-filename={Approved} "
            "{Received}";
        auto pngConverter =
            ApprovalTests::CustomReporter::create( path, arguments );
        bool success = pngConverter->report( inputPath, outputPath );
        if ( !success )
        {
            throw std::runtime_error( "Failed to convert " +
                                      inputPath.string() + " to " +
                                      outputPath.string() );
        }
    }

    return outputPath;
}
