# Preparation

## Before a demo

* Generate branch-coverage results:
    * Make sure `COLLECT_CODE_COVERAGE` is TRUE in top-level CMakeLists.txt
    * Open `demos/02GildedRose/tests/GildedRoseApprovals.cpp`
    * Uncomment test case `VerifyCombinations`
    * Set target to `02GildedRose_branch_coverage`
    * Make that target
    * Check the contents of `cmake-build-debug-clang-90/02GildedRose_branch_coverage`
* Tidy up the repo
    * Revert any changes in code
    * Make sure `COLLECT_CODE_COVERAGE` is FALSE in top-level CMakeLists.txt
    * Build the whole project
    * Run `setup_for_demo.sh`
* Set up the IDE
    * Hide panels
    * Set font size
    * Run -> Hide Coverage
* First demo
    * Set target to `01HelloApprovals`
    * Open `demos/01HelloApprovals/HelloApprovalsTests.cpp`
    * Collapse the block-code-comments
