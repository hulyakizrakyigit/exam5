#include "treebag.hpp"

treebag::treebag(): root(NULL){}

treebag::treebag(const treebag& t){
    root = copy_node(t.root);
}

treebag::~treebag(){
    destroy_node(root);
}

treebag& treebag::operator=(const treebag& t){
    if(this != &t){
        destroy_node(root);
        root = copy_node(t.root);
    }
    return *this;
}

void treebag::insert(int value){
    node** current = &root;
    while(*current){
        if(value < (*current)->value)
            current = &(*current)->left;
        else
            current = &(*current)->right;
    }
    *current = new node();
    (*current)->value = value;
    (*current)->left = NULL;
    (*current)->right = NULL;
}

void treebag::insert(int* arr, int arrsize){
    if(!arr || arrsize < 0){
        return;
    }
    for(int i = 0; i<arrsize; i++)
        insert(arr[i]);
}

void treebag::clear(){
    destroy_node(root);
    root = NULL;
}

void treebag::print()const{
    print_node(root);
    std::cout << std::endl; //kontrol
}

void treebag::print_node(node* n){
    if(n){
        print_node(n->left);
        std::cout << n->value << " ";
        print_node(n->right);
    }
}

void treebag::destroy_node(node *n){
    if(n){
        destroy_node(n->left);
        destroy_node(n->right);
        delete n;
    }
}

treebag::node* treebag::copy_node(node* n){
    if(n){
    node* newnode = new node();
    newnode->value = n->value;
    newnode->left = copy_node(n->left);
    newnode->right = copy_node(n->right);
    return newnode;
    }
    return NULL;
}



