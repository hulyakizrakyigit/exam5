#include "searchabletreebag.hpp"

searchabletreebag::searchabletreebag():treebag(){}

searchabletreebag::~searchabletreebag(){}

searchabletreebag::searchabletreebag(const searchabletreebag& t): treebag(t){
}

searchabletreebag& searchabletreebag::operator=(const searchabletreebag& t){
    if(this != &t)
        treebag::operator=(t);
    return *this;
}

bool searchabletreebag::has(int value)const{
    node* current = root;
    while(current){
        if(current->value == value)
            return true;
        else if(current->value > value)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

