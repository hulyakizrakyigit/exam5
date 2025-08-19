#ifndef TREE_BAG_HPP
#define TREE_BAG_HPP

#include "bag.hpp"

class treebag : virtual public bag {
    protected:
    struct node {
        int value;
        node *left;
        node *right;
    };
        node* root;

    public:
    treebag();
    treebag(const treebag& bag);
    ~treebag();
    treebag& operator=(const treebag& bag);

    node* extracttree();
    void settree(node* newroot);

    virtual void insert(int value);
    virtual void insert(int* array, int arraysize);
    virtual void print() const;
    virtual void clear();

    private:
    static void destroy_tree(node *n);
    static void print_node(node *n);
    static node* copy_node(node *n);

};

#endif