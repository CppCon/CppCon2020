#include "SVGDrawing.h"
#include "SVGReporter.h"

#include <catch2/catch.hpp>
#include <ApprovalTests.hpp>

using namespace ApprovalTests;

TEST_CASE( "SVG Test 1" )
{
    // TODO This test fails: how big is the difference in the image?
    SVGDrawing drawing = createDrawing( "drawing1.svg" );
    Approvals::verify( drawing.content() );
}
