#include <ApprovalTests.hpp>
#include <catch2/catch.hpp>

#include "../lib/GildedRose.h"

// TestHelpers.h provides:
//  1. std::ostream& operator<<( std::ostream& os, const Item& obj );
//  2. Item getUpdatedItem( const std::string& name, int sellIn, int quality );
#include "TestHelpers.h"

using namespace ApprovalTests;

// TODO 1: Measure the LINE coverage in GildedRose.cc achieved in GildedRoseTest.cpp

/* TODO 2: Use ApprovalTests to get to 100% LINE coverage of GildedRose.cc.

         Try to do better than:
           Approvals::verify( Item );
           Approvals::verifyAll( std::vector<Item> );
*/

//TEST_CASE( "VerifyCombinations" )
//{
//    std::vector<std::string> names{
//        "Wibble",
//        "Aged Brie",
//        "Backstage passes to a TAFKAL80ETC concert" }; // Added
//    std::vector<int> sellIns{ 0 };
//    std::vector<int> qualities{ 0, 1, 2 }; // Added: 1, 2
//
//    CombinationApprovals::verifyAllCombinations(
//        []( const std::string& name, int sellIn, int quality ) {
//            return getUpdatedItem( name, sellIn, quality );
//        },
//        names,
//        sellIns,
//        qualities ); // 100% line coverage
//}

/* Approved file starts with:

(Wibble, 0, 0) => name: Wibble, sellIn: -1, quality: 0
(Wibble, 0, 1) => name: Wibble, sellIn: -1, quality: 0
(Wibble, 0, 2) => name: Wibble, sellIn: -1, quality: 0
(Aged Brie, 0, 0) => name: Aged Brie, sellIn: -1, quality: 2

 */

// TODO 3: Understand the branch coverage of GildedRose.cc.

// TODO 4: Use ApprovalTests to get from 75% to 100% BRANCH coverage
//         in GildedRose.cc.

//TEST_CASE( "VerifyMoreCombinations" )
//{
//    std::vector<std::string> names{
//        "Wibble",
//        "Aged Brie",
//        "Backstage passes to a TAFKAL80ETC concert",
//        "Sulfuras, Hand of Ragnaros" };            // Added
//    std::vector<int> sellIns{ -1, 0, 11 };         // Added -1, 11
//    std::vector<int> qualities{ 0, 1, 2, 49, 50 }; // Added 49. 50
//
//    CombinationApprovals::verifyAllCombinations(
//        []( const std::string& name, int sellIn, int quality ) {
//            return getUpdatedItem( name, sellIn, quality );
//        },
//        names,
//        sellIns,
//        qualities ); // 100% line coverage, 100% branch coverage
//}
