#ifndef DEMO_TESTHELPERS_H
#define DEMO_TESTHELPERS_H

#include <iosfwd>

class Item;

std::ostream& operator<<( std::ostream& os, const Item& obj );

// Helper function to reduce boilerplate code
Item getUpdatedItem( const std::string& name,
                     int sellIn,
                     int quality );

#endif //DEMO_TESTHELPERS_H
