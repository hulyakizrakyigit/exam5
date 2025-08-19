
#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm> 

class bigint {
private:
    std::string val;
    void removezero();
    std::string addstring(const std::string& s1, const std::string& s2);

public:
    bigint();
    bigint(unsigned int i);
    bigint(const std::string& val);
    bigint(const bigint& other);
    bigint& operator=(const bigint& other);
    ~bigint();

    bigint operator+(const bigint& b);
    bigint& operator+=(const bigint& b);

    bigint operator++(int);
    bigint& operator++();

    bool operator==(const bigint& b) const;
    bool operator!=(const bigint& b) const;
    bool operator<(const bigint& b) const;
    bool operator>(const bigint& b) const;
    bool operator>=(const bigint& b) const;
    bool operator<=(const bigint& b) const;

    bigint operator<<(const bigint& b);
    bigint operator>>(const bigint& b);
    bigint& operator<<=(const bigint& b);
    bigint& operator>>=(const bigint& b);
    bigint operator<<(unsigned int i);
    bigint operator>>(unsigned int i);
    bigint& operator<<=(unsigned int i);
    bigint& operator>>=(unsigned int i);

    void print(std::ostream &os) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& b);

#endif
