#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "searchablebag.hpp"

class searchablearraybag : public arraybag, public searchablebag {
    public:
    searchablearraybag();
    searchablearraybag(const searchablearraybag& other);
    ~searchablearraybag();
    searchablearraybag& operator=(const searchablearraybag& other);

    virtual bool has(int value) const;

};


#endif
