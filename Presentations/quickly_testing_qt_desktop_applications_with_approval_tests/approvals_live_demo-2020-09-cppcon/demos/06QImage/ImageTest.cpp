#include <catch2/catch.hpp>
#include <ApprovalTests.hpp>
#include <ApprovalTestsQt.hpp>

#include <QImage>

#include "helpers/QImageExamples.h"

using namespace ApprovalTests;

// TODO 1: Run this, and understand the output
TEST_CASE( "It approves QImages" )
{
//    auto defaultReporterDisposer = Approvals::useAsDefaultReporter(
//        std::make_shared<Mac::BeyondCompareReporter>() );

    QImage image = QImageExamples::createImage( "red" );
    ApprovalTestsQt::verifyQImage( image );
}
