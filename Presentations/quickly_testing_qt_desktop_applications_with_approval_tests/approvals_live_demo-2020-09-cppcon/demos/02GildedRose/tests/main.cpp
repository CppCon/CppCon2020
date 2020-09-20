#define APPROVALS_CATCH
#include "ApprovalTests.hpp"

using namespace ApprovalTests;

auto directoryDisposer =
    Approvals::useApprovalsSubdirectory( "approval_tests" );
