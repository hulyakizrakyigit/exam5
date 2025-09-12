#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

class vect2{
    private:
    int x;
    int y;

    public:
    vect2();
    vect2(int x, int y);
    vect2(const vect2& o);
    vect2& operator=(const vect2& o);
    ~vect2();

    int operator[](int index)const;
    int& operator[](int index);

    vect2 operator++(int);
    vect2& operator++();
    vect2 operator--(int);
    vect2& operator--();

    vect2 operator+(int i);
    vect2 operator+(const vect2& o)const;
    vect2& operator+=(int i);
    vect2& operator+=(const vect2& o);

    vect2 operator-(int i);
    vect2 operator-(const vect2& o);
    vect2& operator-=(int i);
    vect2& operator-=(const vect2& o);

    vect2 operator*(int i)const;
    vect2 operator*(const vect2& o);
    vect2& operator*=(int i);
    vect2& operator*=(const vect2& o);

    bool operator==(const vect2& o);
    bool operator!=(const vect2& o);

    vect2 operator-()const;

};

vect2 operator*(const int num, const vect2& o);
vect2 operator+(int num, const vect2& o);
vect2 operator-(int num, const vect2& o);

std::ostream& operator<<(std::ostream& os, const vect2& o);

#endif