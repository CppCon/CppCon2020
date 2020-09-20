# 2 GildedRose

A worked example of the [cpp version of Emily Bache's GildedRose Refactoring Kata](https://github.com/emilybache/GildedRose-Refactoring-Kata/tree/master/cpp).

## Features used in demo

* **Line coverage**
    * Turning on line code coverage
    * Viewing line code coverage in CLion
* **Branch/condition coverage**
    * Collecting branch code coverage
    * Viewing branch code coverage
* std::ostream& operator<<()
* CombinationApprovals::**verifyAllCombinations**()
* Approvals::**useApprovalsSubdirectory**()

## Takeaways

* Think about the formatting of the output, so it's easy to understand any failures
* verifyAllCombinations() shows inputs and outputs, which is really useful
* If measuring coverage of your tests, try to check branch coverage

## Approval Tests helps with Legacy Code

* Get good coverage
* Before you start refactoring the legacy code
* verifyAllCombinations() is also useful for testing wide range of values
    * So good for coverage even with new code, when multiple inputs

## Setup

For help setting up code-coverage measurements, see:

* https://github.com/claremacrae/talks/blob/main/HowTos/Set_up_Code_Coverage_on_Windows.md
* https://github.com/claremacrae/talks/blob/main/HowTos/Set_up_Code_Coverage_on_macOS.md
