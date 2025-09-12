#ifndef SEARCHABLETREEBAG_HPP
#define SEARCHABLETREEBAG_HPP

#include "treebag.hpp"
#include "searchablebag.hpp"

class searchabletreebag: public treebag, public searchablebag{
    public:
    searchabletreebag();
    searchabletreebag(const searchabletreebag& o);
    searchabletreebag& operator=(const searchabletreebag& o);
    ~searchabletreebag();

    bool has(int value)const;

};


#endif