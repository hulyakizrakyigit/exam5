#ifndef SEARCHABLEARRAYBAG_HPP
#define SEARCHABLEARRAYBAG_HPP

#include "arraybag.hpp"
#include "searchablebag.hpp"

class searchablearraybag: public arraybag, public searchablebag{
    public:
    searchablearraybag();
    searchablearraybag(const searchablearraybag& o);
    searchablearraybag& operator=(const searchablearraybag& o);
    ~searchablearraybag();

    bool has(int value)const;

};

#endif