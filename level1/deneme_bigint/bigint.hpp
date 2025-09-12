#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

class bigint{
    private:
    std::string val;
    void removezero();
    std::string addstring(const std::string& a, const std::string& b);

    public:
    bigint();           // int constructor eklendi
    bigint(unsigned int i);
    bigint(const std::string& val2);
    bigint(const bigint& o);
    bigint& operator=(const bigint& o);

    bigint operator++(int);
    bigint& operator++();

    bigint operator+(const bigint& b);
    bigint& operator+=(const bigint& b);

    bool operator==(const bigint& o)const;
    bool operator!=(const bigint& o)const;
    bool operator<=(const bigint& o)const;
    bool operator<(const bigint& o)const;
    bool operator>(const bigint& o)const;
    bool operator>=(const bigint& o)const;

    bigint operator<<(const bigint& other);
    bigint operator>>(const bigint& other);
    bigint& operator<<=(const bigint& other);
    bigint& operator>>=(const bigint& other);

    bigint operator<<(unsigned int n);
    bigint operator>>(unsigned int n);
    bigint& operator<<=(unsigned int n);
    bigint& operator>>=(unsigned int n);

    void print(std::ostream& os)const;
};

std::ostream& operator<<(std::ostream& os, const bigint& b);

#endif