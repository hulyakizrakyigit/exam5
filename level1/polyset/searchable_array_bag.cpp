#include "searchable_array_bag.hpp"

#include <iostream>

searchablearraybag::searchablearraybag() : arraybag() {}

searchablearraybag::searchablearraybag(const searchablearraybag& other) : arraybag(other) {}

searchablearraybag::~searchablearraybag() {}

searchablearraybag& searchablearraybag::operator=(const searchablearraybag& other){
    if (this != &other) 
        arraybag::operator=(other);
    return *this;
}

bool searchablearraybag::has(int value) const {
    for (int i = 0; i < size; ++i)
        if(data[i] == value)
            return true;
    return false;
}