#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
struct Node {
        T key;
        Node* parent;
        Node* left;
        Node* right;
        int height;
} ;

template <typename T>
class BSTNode{
        //todo

    Node<T>* find(T k);
    Node<T>* find_min(T k);
    Node<T>* next_larger(Node<T>* x);
    void insert(T k);
    Node<T>* delet(T k);

};

template <typename T>
class BSTree
{
protected:
    Node<T> *root;
public:
    BSTree(/* args */){

    }
    ~BSTree(){

    }
    Node<T>* find(T k);
    Node<T>* find_min(T k);
    Node<T>* next_larger(Node<T>* x);
    void insert(T k);
    Node<T>* delet(T k);
};


template <typename T>
class AVLTree : public BSTree<T> {

public:
    int height(Node<T>* x){  return x->height; }

    void update_height(Node<T>* x) {
        if (x == nullptr) 
            x->height = -1;
        else
            x->height = max(x->left->height, x->right->height) + 1;
    }

    void left_rotate(Node<T>* x){
        Node<T>* y = x->right;
        y->parent = x->parent;
        if (y->parent == nullptr)
            this->root = y;
        if (y->parent->left == x)
            y->parent->left  = y;
        else if (y->parent->right == x)
            y->parent->right = y;

        x->right = y->left;
        if (y->left) 
            y->left->parent = x;
        x->parent = y;
        y->left = x;
        update_height(x);
        update_height(y);
    }

    void right_rotate(Node<T>* x){
        Node<T>* y = x->left;
        y->parent = x->parent;
        if (y->parent == nullptr)
            this->root = y;
        if (y->parent->left == x)
            y->parent->left  = y;
        else if (y->parent->right == x)
            y->parent->right = y;
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
        x->parent = y;
        y->right = x;
        update_height(x);
        update_height(y);
    }

    void rebalance(Node<T>* x){
        while (x) {
            update_height(x);
            if (x->left->height + 2 <= x->right->height){
                if (x->right->left->height <= x->right->right->height)
                    left_rotate(x);
                else{
                    right_rotate(x->right);
                    left_rotate(x);
                }
            }
            else if (x->right->height + 2 <= x->left->height){
                if (x->left->right->height <= x->left->left->height)
                    right_rotate(x);
                else {
                    left_rotate(x->left);
                    right_rotate(x);
                }
            }
            x = x->parent;
        }
    }
    void insert(T k) {

    }

};


int main()
{
    AVLTree<int> avltree;
    for (int i = 1; i < 9; i++){
        avltree.insert(i);
    }
    for (int i = 1; i < 9; i++){
        // avltree.remove(i);
    }
    
}