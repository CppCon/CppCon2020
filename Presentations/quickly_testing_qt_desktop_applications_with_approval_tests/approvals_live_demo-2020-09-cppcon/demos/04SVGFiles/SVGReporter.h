#ifndef DEMO_SVGREPORTER_H
#define DEMO_SVGREPORTER_H

#include <ApprovalTests.hpp>

class SVGReporter : public ApprovalTests::Reporter
{
public:
    bool report( std::string receivedSVGFile,
                 std::string approvedSVGFile ) const override;

    // Return the name of the saved .png file
    std::string convertToPNG( std::string SVGFile ) const;
};

#endif //DEMO_SVGREPORTER_H
