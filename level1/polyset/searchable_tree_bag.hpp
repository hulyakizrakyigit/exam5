#ifndef SEARCHABLE_TREE_BAG_HPP
#define SEARCHABLE_TREE_BAG_HPP

#include "tree_bag.hpp"
#include "searchablebag.hpp"

class searchabletreebag : public treebag, public searchablebag {
    public:
    searchabletreebag();
    searchabletreebag(const searchabletreebag& other);
    ~searchabletreebag();
    searchabletreebag& operator=(const searchabletreebag& other);

    virtual bool has(int value) const;


};

#endif
