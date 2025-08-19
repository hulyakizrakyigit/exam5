#ifndef ARRAY_BAG_HPP
#define ARRAY_BAG_HPP


#include "bag.hpp"

class arraybag: virtual public bag {
    protected:
    int* data;
    int size;

    public:
    arraybag();
    arraybag(const arraybag& other);
    ~arraybag();
    arraybag& operator=(const arraybag& other);

    void insert(int value);
    void insert(int* array, int arraysize);
    void print() const;
    void clear();

};

#endif