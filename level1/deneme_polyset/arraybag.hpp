#ifndef ARRAYBAG_HPP
#define ARRAYBAG_HPP

#include "bag.hpp"

class arraybag: virtual public bag{
    protected:
    int* data;
    int size;

    public:
    arraybag();
    ~arraybag();
    arraybag(const arraybag& a);
    arraybag& operator=(const arraybag& a);

    void insert(int);
    void insert(int* , int);
    void print()const;
    void clear();


};

#endif