#include <ApprovalTests.hpp>
#include <catch2/catch.hpp>

#include "../../lib/GildedRose.h"
#include "../TestHelpers.h"

using namespace ApprovalTests;

/* TODO: Use ApprovalTests to get to 100% line and branch coverage
         of GildedRose.cc.

   For help setting up code-coverage measurements, see:
    * https://github.com/claremacrae/talks/blob/main/HowTos/Set_up_Code_Coverage_on_Windows.md
    * https://github.com/claremacrae/talks/blob/main/HowTos/Set_up_Code_Coverage_on_macOS.md

   NOTE: All tests are disabled initially, with Catch's "[!hide]" tag
*/

TEST_CASE( "TestOneValue2", "[!hide]" )
{
    std::vector<Item> items;
    items.emplace_back( Item( "Wibble", 0, 0 ) );
    GildedRose app( items );
    app.updateQuality();
    Approvals::verify( app.items[0] ); // 51% line coverage
}

/* Things to note
 * 1. If this is run without adding a main() for Approvals, it will give
 *    a meaningful help message explaining what to do.
 * 2. The "approved" file will contain this output: Note how it easily allows us to test
 *    the Item's whole content, rather than needing one test per value.
 *     name: Wibble, sellIn: -1, quality: 0
 *    i.e. the actual calculation result (new quality) is now tested
 * 3. If we are testing a class that has its own output stream operator, Approvals
 *    would use that automatically. As Item doesn't have one, we provide
 *    an implementation here in the testsuite.
 * 3. Still only 51% coverage of GildedRose.cpp
 */

TEST_CASE( "TestMultipleValues2", "[!hide]" )
{
    std::vector<Item> items;
    items.emplace_back( Item( "Wibble", 0, 0 ) );
    items.emplace_back( Item( "Aged Brie", 0, 0 ) ); // Added
    GildedRose app( items );
    app.updateQuality();
    Approvals::verifyAll( app.items ); // 65% line coverage
}

/* Things to note
 * 1. By using Approvals::verifyAll, it is easy to add extra values to test
 * 2. Test coverage up to 65% on GildedRose.cpp
 * 3. The test output now looks like this, showing the indices of the objects
 *    after they have been updated. They don't show the initial values though.

[0] = name: Wibble, sellIn: -1, quality: 0
[1] = name: Aged Brie, sellIn: -1, quality: 2

 */

TEST_CASE( "VerifyCombinations2", "[!hide]" )
{
    std::vector<std::string> names{ "Wibble", "Aged Brie" };
    std::vector<int> sellIns{ 0 };
    std::vector<int> qualities{ 0 };

    CombinationApprovals::verifyAllCombinations(
        []( const std::string& name, int sellIn, int quality ) {
            return getUpdatedItem( name, sellIn, quality );
        },
        names,
        sellIns,
        qualities ); // 65% line coverage
}

/* Things to note
 * 1. By using Approvals::verifyAllCombinations, it is easy to add many
 *    extra values to test.
 * 2. Test coverage still 67% on GildedRose.cpp, as inputs are unchanged
 * 3. The test output now looks like this, showing the indices of the objects
 *    after they have been updated. They don't show the initial values though.

(Wibble, 0, 0) => name: Wibble, sellIn: -1, quality: 0
(Aged Brie, 0, 0) => name: Aged Brie, sellIn: -1, quality: 2

 */

TEST_CASE( "VerifyMoreCombinations2", "[!hide]" )
{
    std::vector<std::string> names{
        "Wibble",
        "Aged Brie",
        "Backstage passes to a TAFKAL80ETC concert" }; // Added
    std::vector<int> sellIns{ 0 };
    std::vector<int> qualities{ 0, 1, 2 }; // Added: 1, 2

    CombinationApprovals::verifyAllCombinations(
        []( const std::string& name, int sellIn, int quality ) {
            return getUpdatedItem( name, sellIn, quality );
        },
        names,
        sellIns,
        qualities ); // 100% line coverage, 75% branch coverage
}

/* Things to note
 * 1. Test coverage at 100% on GildedRose.cpp, according to OpenCppCoverage
 * 2. But there are many values in the source code that are not mentioned
 *    in our tests. We haven't covered all the unwritten 'else' cases.
 * 3. So branch coverage is less than 100%.
 * 4. After I added dummy else blocks to all the if statements in
 *    GildedRose.cpp, coverage was 83%.
 */

TEST_CASE( "VerifyEvenMoreCombinations2", "[!hide]" )
{
    std::vector<std::string> names{
        "Wibble",
        "Aged Brie",
        "Backstage passes to a TAFKAL80ETC concert",
        "Sulfuras, Hand of Ragnaros" };            // Added
    std::vector<int> sellIns{ -1, 0, 11 };         // Added -1, 11
    std::vector<int> qualities{ 0, 1, 2, 49, 50 }; // Added 49. 50

    CombinationApprovals::verifyAllCombinations(
        []( const std::string& name, int sellIn, int quality ) {
            return getUpdatedItem( name, sellIn, quality );
        },
        names,
        sellIns,
        qualities ); // 100% line coverage, 100% branch coverage
}

/* Things to note
 * 1. Test coverage at 100% on GildedRose.cpp, according to OpenCppCoverage,
 *    after adding else blocks in that file, to test more boolean combinations
 * 2. So branch coverage is now 100%.
 * 3. We would be able to refactor pretty confidently.
 */

TEST_CASE( "VerifyEvenMoreCombinationsAfterMutation2", "[!hide]" )
{
    std::vector<std::string> names{
        "Wibble",
        "Aged Brie",
        "Backstage passes to a TAFKAL80ETC concert",
        "Sulfuras, Hand of Ragnaros" };
    std::vector<int> sellIns{ -1, 0, 2, 6, 11 }; // Added 2, 6
    std::vector<int> qualities{ 0, 1, 2, 49, 50 };

    CombinationApprovals::verifyAllCombinations(
        []( const std::string& name, int sellIn, int quality ) {
            return getUpdatedItem( name, sellIn, quality );
        },
        names,
        sellIns,
        qualities ); // 100% line coverage, 100% branch coverage
}

/* Things to note
 * 1. Using manual mutation testing, found two more cases that were not
 *    detected, needing extra tests
 * 2. We would be able to refactor even more confidently.
 */
