#ifndef VECT2_HPP
#define VECT2_HPP

#include <string>
#include <iostream>

class vect2
{
    private:
    int x;
    int y;

    public:
    vect2();
    vect2(int x, int y);
    vect2(const vect2 &other);
    vect2& operator=(const vect2& other);
    ~vect2();

    int operator[](int idx) const;
    int& operator[](int idx);

    vect2 operator++(int);
    vect2& operator++();
    vect2& operator--();
    vect2 operator--(int);

    vect2& operator+=(int i);
    vect2& operator-=(int i);
    vect2& operator+=(const vect2& other);
    vect2& operator-=(const vect2& other);
    vect2& operator*=(int i);
    vect2& operator*=(const vect2& other);

    vect2 operator-() const;

    vect2 operator+(int i)const;
    vect2 operator+(const vect2& other) const;
    vect2 operator-(int i)const;
    vect2 operator-(const vect2& other)const;
    vect2 operator*(const int i)const;
    vect2 operator*(const vect2& other)const;

    bool operator==(const vect2& other);
    bool operator!=(const vect2& other);


};

vect2 operator*(int num, const vect2& other);

std::ostream& operator<<(std::ostream& os, const vect2& other);

#endif