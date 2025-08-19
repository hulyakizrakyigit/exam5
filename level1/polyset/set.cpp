#include "set.hpp"

set::set(searchablebag* bag) : bag(bag) {}

// set::set(const set& other) : bag(other.bag) {} // Shallow copy

set::set(const set& other) {
        if (!other.bag) {
            bag = NULL;
            return ;
        }
    searchablearraybag* arrbag = dynamic_cast<searchablearraybag *>(other.bag);
    if (arrbag)
    {
        bag = new searchablearraybag(*arrbag);
    }
    else {
        searchabletreebag* tbag = dynamic_cast<searchabletreebag *>(other.bag);
        if (tbag)
            bag = new searchabletreebag(*tbag);
        else
            bag = NULL;
    }
}

set::~set(){

}


set& set::operator=(const set& other) {
    if (this != &other)
    {
        delete bag;
        
        if (!other.bag) {
            bag = NULL;
            return *this;
        }
        searchablearraybag* arrbag = dynamic_cast<searchablearraybag *>(other.bag);
    if (arrbag)
    {
        bag = new searchablearraybag(*arrbag);
    }
    else {
        searchabletreebag* tbag = dynamic_cast<searchabletreebag *>(other.bag);
        if (tbag)
            bag = new searchabletreebag(*tbag);
        else
            bag = NULL;
    }
    }
    return *this;
}

// set& set::operator=(const set& other) {
//     if (this != &other) {
//         bag = other.bag; // Shallow copy
//     }
//     return *this;
// }

void set::insert(int value) {
    if (bag && !bag->has(value))
        bag->insert(value);
}

void set::insert(int *values, int size) {
    if (!values || size <= 0)
    {
        return;
    }
    
        for (int i = 0; i < size; i++)
        {
            if (!bag->has(values[i]))
                bag->insert(values[i]);
        }
}

bool set::has(int value) const {
    return bag ? bag->has(value) : false;
}

void set::print() const{
    if (bag)
    bag->print();
}

void set::clear() {
    if (bag)
    bag->clear();
}
