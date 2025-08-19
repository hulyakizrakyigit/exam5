#include "vect2.hpp"

 vect2::vect2()
 {
    this->x = 0;
    this->y = 0;
 }

 vect2::vect2(int x, int y)
{
    this->x = x;
    this->y = y;
}

vect2::vect2(const vect2& other)
{
    this->x = other.x;
    this->y = other.y;
}

vect2& vect2::operator=(const vect2& other)
{
    if(this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

vect2::~vect2() {}

int vect2::operator[](int idx) const
{
    if (idx == 0)
        return x;
    return y;
}

int& vect2::operator[](int idx)
{
    if (idx == 0)
        return x;
    return y;
}



vect2 vect2::operator++(int) {
    vect2 temp = *this;
    ++(*this);
    return temp;
}

vect2& vect2::operator++() {
    this->x++;
    this->y++;
    return *this;
}

vect2& vect2::operator--() {
    this->x--;
    this->y--;
    return *this;
}

vect2 vect2::operator--(int) {
    vect2 temp = *this;
    --(*this);
    return temp;
}

vect2& vect2::operator+=(int i) {
    this->x += i;
    this->y += i;
    return *this;
}

vect2& vect2::operator-=(int i) {
    this->x -= i;
    this->y -= i;
    return *this;
}

vect2& vect2::operator*=(int i) {
    this->x *= i;
    this->y *= i;
    return *this;
}

vect2& vect2::operator*=(const vect2& other) {
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

vect2& vect2::operator+=(const vect2& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

vect2& vect2::operator-=(const vect2& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

vect2 vect2::operator-()const{
    return vect2(-(this->x), -(this->y));
}

vect2 vect2::operator+(int i) {
    vect2 vect(x + i, y + i);
    return vect;
}

vect2 vect2::operator-(int i) {
    vect2 vect(x - i, y - i);
    return vect;
}

vect2 vect2::operator*(const int i) const{
    vect2 vect(x * i, y * i);
    return vect;
}

vect2 vect2::operator+(const vect2& other) const {
    vect2 vect(x + other.x, y + other.y);
    return vect;
}

vect2 vect2::operator-(const vect2& other) {
    vect2 vect(x - other.x, y - other.y);
    return vect;
}

vect2 vect2::operator*(const vect2& other) {
    vect2 vect(x * other.x, y * other.y);
    return vect;
}

bool vect2::operator==(const vect2& other) {
    return (x == other.x && y == other.y);
}

bool vect2::operator!=(const vect2& other) {
    return (x != other.x || y != other.y);
}




vect2 operator*(int num, const vect2& other) {
    vect2 tmp(other);
    tmp *= num;
    return tmp;
}


std::ostream& operator<<(std::ostream& os, const vect2& other)
{
    std::cout << "{" << other[0] << ", " << other[1] << "}";
    return os;
}