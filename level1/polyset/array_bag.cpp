#include "array_bag.hpp"

arraybag::arraybag(): data(NULL), size(0){}

arraybag::arraybag(const arraybag& other) : data(NULL), size(0){
    if (other.size > 0) {
        data = new int[other.size];
        size = other.size;
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }
}

arraybag::~arraybag() {
    delete[] data;
}

arraybag& arraybag::operator=(const arraybag& other) {
    if (this != &other) {
        clear();
        if (other.size > 0) {
            data = new int[other.size];
            size = other.size;
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
    }
    return *this;
}

void arraybag::insert(int value) {
    int *newdata = new int[size + 1];
    for (int i = 0; i < size; i++)
        newdata[i] = data[i];
    newdata[size] = value;
    delete[] data;
    data = newdata;
    size++;
}

void arraybag::insert(int* array, int arraysize) {
    if (!array || arraysize <= 0)
        return;
    for (int i = 0; i < arraysize; i++)
        insert(array[i]);
}

void arraybag::print() const{
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
     std::cout << std::endl;
}

void arraybag::clear() {
    delete[] data;
    data = NULL;
    size = 0;
}

