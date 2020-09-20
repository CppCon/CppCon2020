#include <catch2/catch.hpp>
#include <ApprovalTestsQt.hpp>

#include <QTableWidget>

#include "helpers/QTableWidgetExamples.h"

using namespace ApprovalTestsQt;

// Scenario: Some code that mixes doing some calculations
//           with putting the results in to a table widget.
// TODO 1: Use ApprovalTestsQt to save the table content
// TODO 2: Review verifyQTableView()
TEST_CASE( "It approves a QTableWidget" )
{
    QTableWidget tableWidget;
    QTableWidgetExamples::populateTable( tableWidget );

    ApprovalTestsQt::verifyQTableView( tableWidget );
}
