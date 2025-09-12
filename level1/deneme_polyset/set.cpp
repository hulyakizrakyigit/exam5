#include "set.hpp"

set::set():bag(NULL){}

set::set(searchablebag *b): bag(b){}

set::set(const set& s){
    if(!s.bag)
        bag = NULL;
    
    searchablearraybag *arrbag = dynamic_cast<searchablearraybag *>(s.bag);
    if(arrbag)
    {
        bag = new searchablearraybag(*arrbag);
    }
    else{
        searchabletreebag *tbag = dynamic_cast<searchabletreebag *>(s.bag);
        if(tbag){
            bag = new searchabletreebag(*tbag);
        }
        else
            bag = NULL;
    }
}

set& set::operator=(const set& s){
    if(this != &s){
        clear(); //kontrol
    if(!s.bag)
        bag = NULL;
    
    searchablearraybag *arrbag = dynamic_cast<searchablearraybag *>(s.bag);
    if(arrbag)
    {
        bag = new searchablearraybag(*arrbag);
    }
    else{
        searchabletreebag *tbag = dynamic_cast<searchabletreebag *>(s.bag);
        if(tbag){
            bag = new searchabletreebag(*tbag);
        }
        else
            bag = NULL;
    }
    }
    return *this;
}

void set::print()const{
    bag->print();
}

void set::clear(){
    bag->clear();
}

void set::insert(int value){
    if(bag && !bag->has(value))
        bag->insert(value);
}

void set::insert(int *arr, int arrsize){
    if(!arr || arrsize < 0) // kontrol
        return;
    for(int i = 0; i < arrsize; i++){
        if(bag && !bag->has(arr[i]))
        bag->insert(arr[i]);
    }
}

bool set::has(int value)const{
    if(bag)
        return bag->has(value);
    return false;
}

set::~set(){}