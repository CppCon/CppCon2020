#include "TestHelpers.h"
#include "../lib/GildedRose.h"

#include <iostream>

std::ostream& operator<<( std::ostream& os, const Item& obj )
{
    // clang-format off
    return os
        << "name: " << obj.name
        << ", sellIn: " << obj.sellIn
        << ", quality: " << obj.quality;
    // clang-format on
}

Item getUpdatedItem( const std::string& name,
                     int sellIn,
                     int quality )
{
    std::vector<Item> items;
    items.emplace_back( Item( name, sellIn, quality ) );
    GildedRose app( items );

    app.updateQuality();

    return app.items[0];
}
