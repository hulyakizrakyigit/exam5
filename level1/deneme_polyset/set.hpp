#ifndef SET_HPP
#define SET_HPP

#include "searchablearraybag.hpp"
#include "searchabletreebag.hpp"
#include "bag.hpp"
#include "searchablebag.hpp"

class set{
    private:
    searchablebag *bag;

    public:
    set();
    set(searchablebag *b);
    set(const set& s);
    virtual ~set();
    set& operator=(const set& s);

    void insert(int);
    void insert(int* , int);
    void print()const;
    void clear();
    bool has(int value)const;

};


#endif