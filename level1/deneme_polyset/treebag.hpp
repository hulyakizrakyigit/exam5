#ifndef TREEBAG_HPP
#define TREEBAG_HPP

#include "bag.hpp"

class treebag :  virtual public bag{
    protected:
    struct node{
        int value;
        node* left;
        node* right;
    };

    node* root;

    public:
    treebag();
    ~treebag();
    treebag(const treebag& t);
    treebag& operator=(const treebag& t);

    void insert(int);
    void insert(int* , int);
    void print()const;
    void clear();

    static void print_node(node*);
    static void destroy_node(node*);
    static node* copy_node(node*);

};

#endif