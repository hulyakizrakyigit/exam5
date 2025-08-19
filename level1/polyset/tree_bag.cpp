#include "tree_bag.hpp"

#include <iostream>

treebag::treebag() : root(NULL){}

treebag::treebag(const treebag& other) {
    root = copy_node(other.root);
}

treebag::~treebag() {
    clear();
}

treebag& treebag::operator=(const treebag& other) {
    if(this != &other) {
        clear();
        root = other.root;
    }
    return *this;
}

treebag::node* treebag::extracttree() {

    node* temp = root;
    root = NULL;
    return temp;
}

void treebag::settree(node* newroot) {
    clear();
    root = newroot;
}


void treebag::insert(int value) {
    node** current = &root;
    while(*current) {
        if (value < (*current)->value)
            current = &((*current)->left);
        else
            current = &((*current)->right);
    }
    *current = new node();
    (*current)->value = value;
    (*current)->left = NULL;
    (*current)->right = NULL;
}

void treebag::insert(int* array, int size) {
    for (int i = 0; i < size; i++)
        insert(array[i]);
}

void treebag::print() const {
    print_node(root);
    std::cout << std::endl;
}

void treebag::clear() {
    destroy_tree(root);
    root = NULL;
}

void treebag::destroy_tree(node* n) {
    if (n) {
        destroy_tree(n->left);
        destroy_tree(n->right);
        delete n;
    }
}

void treebag::print_node(node *n) {
    if (n) {
        print_node(n->left);
        std::cout << n->value << " ";
        print_node(n->right);
    }
}

treebag::node* treebag::copy_node(node* n) {
    if (!n)
        return NULL;

    node* newnode = new node();
    newnode->value = n->value;
    newnode->left = copy_node(n->left);
    newnode->right = copy_node(n->right);
    return newnode;
}
