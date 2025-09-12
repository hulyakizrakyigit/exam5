#ifndef SEARCHABLEBAG_HPP
#define SEARCHABLEBAG_HPP


#include "bag.hpp"

class searchablebag: virtual public bag{
    public:
    virtual bool has(int)const = 0;
};

#endif