#include "searchable_tree_bag.hpp"

searchabletreebag::searchabletreebag() : treebag() {}

searchabletreebag::searchabletreebag(const searchabletreebag& other) : treebag(other) {}

searchabletreebag::~searchabletreebag() {}

searchabletreebag& searchabletreebag::operator=(const searchabletreebag& other) {
    if (this != &other)
        treebag::operator=(other);
    return *this;
}

bool searchabletreebag::has(int value) const {
    node* current = root;
    while (current)
    {
        if (current->value == value)
            return true;
        else if (current->value > value)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}