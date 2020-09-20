# 1 HelloApprovals

This intentionally trivial example shows:

## Starting Point

* **CHECK() = traditional Catch2 unit test**
* Scenario
    * Perhaps test is being written after feature was done
    * Or perhaps you are adding test for legacy/untested code
* Inputs and outputs from tests are both in the code

## main.cpp

* Help messages (misconfigured main) rather than error messages
    * With CLion, do need to be using CLion 2020.2 EAP or later
    * Only works with v.10.1.0 and earlier
* **Setting up your main**
* Which test frameworks are supported

## HelloApprovalsTests.cpp

* **Reporter**
    * Diff tool popping if there are differences to show
    * No diff tool popping up if test passes
* Separation of test code and data
* Namespace ApprovalTests
* Automated naming of output files
    * approved.txt
    * received.txt
