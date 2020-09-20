/* Traditional main for using Catch2:
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
*/

// Does the above, and also tells
// ApprovalTests to integrate with Catch2 tests:
#define APPROVALS_CATCH
#include "ApprovalTests.hpp"

// For what to use for other test frameworks, see
//  https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredMain.md#error-when-running-tests