#include "searchablearraybag.hpp"

searchablearraybag::searchablearraybag():arraybag(){}

searchablearraybag::~searchablearraybag(){}

searchablearraybag::searchablearraybag(const searchablearraybag& o): arraybag(o){}

searchablearraybag& searchablearraybag::operator=(const searchablearraybag& o){
    if(this != &o)
        arraybag::operator=(o);
    return *this;
}

bool searchablearraybag::has(int value)const{
    for(int i = 0; i < size; i++){
        if(data[i] == value)
            return true;
    }
    return false;
}