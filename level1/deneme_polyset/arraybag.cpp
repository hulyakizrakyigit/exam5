#include "arraybag.hpp"

arraybag::arraybag():data(NULL), size(0){}

arraybag::~arraybag(){
    delete[] data;
}

arraybag::arraybag(const arraybag& other): data(NULL), size(0){
    if(other.size > 0){
        data = new int[other.size];
        for(int i = 0; i < other.size; i++){
            data[i] = other.data[i];
        }
        size = other.size;
    }
}

arraybag& arraybag::operator=(const arraybag& other){
    if(this != &other){
        delete[] data;
        data = NULL;
        size = 0;
        
        if(other.size > 0){
            data = new int[other.size];
            for(int i = 0; i < other.size; i++){
                data[i] = other.data[i];
            }
            size = other.size;
        }
    }
    return *this;
}void arraybag::insert(int value){
    int* nd = new int[size + 1];
    for(int i = 0; i< size; i++){
        nd[i] = data[i];
    }
    data = nd;
    nd[size] = value;
    size++;
}

void arraybag::insert(int* arr, int arrsize){
    if(!arr || arrsize < 0)
        return;
    for(int i = 0; i < arrsize; i++){
        insert(arr[i]);
    }
}

void arraybag::clear(){
    delete[] data;
    data = NULL;
    size = 0;
}

void arraybag::print()const{
    for(int i = 0; i < size; i++){
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}