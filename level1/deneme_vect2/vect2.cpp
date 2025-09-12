#include "vect2.hpp"

vect2::vect2():x(0), y(0){}

vect2::vect2(int x, int y):x(x), y(y){}

vect2::~vect2(){}

vect2::vect2(const vect2& o){
    x = o.x;
    y = o.y;
}

vect2& vect2::operator=(const vect2& o){
    if(this != &o){
          x = o.x;
        y = o.y;
    }
    return *this;
}

int vect2::operator[](int i)const{
    if(i == 0)
        return x;
    return y;
}

int& vect2::operator[](int i){
    if(i == 0)
        return x;
    return y;
}

vect2 vect2::operator++(int){
    vect2 tmp(*this);
    x++;
    y++;
    return tmp;
}

vect2& vect2::operator++(){
    x++;
    y++;
    return *this;
}

vect2 vect2::operator--(int){
    vect2 tmp(*this);
    x--;
    y--;
    return tmp;
}

vect2& vect2::operator--(){
    x--;
    y--;
    return *this;
}

vect2 vect2::operator+(int i){
    return vect2(x+i, y+i);
}

vect2 vect2::operator-(int i){
    return vect2(x-i, y-i);
}

vect2 vect2::operator*(int i)const{
    vect2 vec(x*i, y*i);
    return vec;
}

vect2 vect2::operator+(const vect2& o)const{
    return vect2(x+o.x, y+o.y);
}

vect2 vect2::operator-(const vect2& o){
    return vect2(x-o.x, y-o.y);
}
vect2 vect2::operator*(const vect2& o){
    return vect2(x*o.x, y*o.y);
}

vect2& vect2::operator+=(int i){
    x += i;
    y += i;
    return *this;
}

vect2& vect2::operator-=(int i){
    x -= i;
    y -= i;
    return *this;
}
vect2& vect2::operator*=(int i){
    x *= i;
    y *= i;
    return *this;
}

vect2& vect2::operator+=(const vect2& o){
    x += o.x;
    y += o.y;
    return *this;
}

vect2& vect2::operator-=(const vect2& o){
    x -= o.x;
    y -= o.y;
    return *this;
}

vect2& vect2::operator*=(const vect2& o){
    x *= o.x;
    y *= o.y;
    return *this;
}

bool vect2::operator==(const vect2& o){
    return x == o.x && y == o.y;
}

bool vect2::operator!=(const vect2& o){
    return x != o.x || y != o.y;
}

vect2 vect2::operator-()const{
    return vect2(-x, -y);
}

vect2 operator*(const int num, const vect2& o){
    vect2 tmp(o);
    tmp *= num;
    return tmp;
}

vect2 operator+(int num, const vect2& o){
    vect2 tmp(o);
    tmp += num;
    return tmp;
}
vect2 operator-(int num, const vect2& o){
    vect2 tmp(o);
    tmp -= num;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const vect2& v){
    os << v[0] << " " << v[1];
    return os;
}