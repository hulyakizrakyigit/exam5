#ifndef SET_HPP
#define SET_HPP

#include "searchablebag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set {
    private:
    searchablebag* bag;

    public:
    set();
    set(searchablebag* bag);
    set(const set& other);
    virtual ~set();
    set& operator=(const set& other);

    void insert(int value);
    void insert(int* , int);
    bool has(int value) const;
    void print() const;
    void clear();
};

#endif