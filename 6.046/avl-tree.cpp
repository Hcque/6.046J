#include <algorithm>
// #include <stdlib>
#include <cassert>
#include <iostream>
using namespace std;

template <typename T>
class BSTNode{
public:

    T key;
    BSTNode<T>* parent;
    BSTNode<T>* left;
    BSTNode<T>* right;
    int height;
    
    BSTNode<T>(T k) : key(k) {}

    BSTNode<T>* find(T k){
        if (k == key) return this;
        else if (k < key){
            if (left == nullptr) return nullptr;
            else return left->find(k);
        }
        else {
            if (right == nullptr) return nullptr;
            else return right->find(k);
        }
    }
    BSTNode<T>* findMin(){
        BSTNode<T>* cur = this;
        while (cur->left != nullptr)
            cur = cur->left;
        return cur;
    }

    BSTNode<T>* nextLarger (){
        assert (this != nullptr);
        if (this->right != nullptr)
            return this->right->findMin();
        BSTNode<T>* cur = this;
        while (cur->parent != nullptr && cur->parent->right == cur)
            cur = cur->parent;
        return cur->parent;
    }
    void insert(BSTNode<T>* n){
        if (n != nullptr) return;
        if (n->key < this->key){
            if (this->left != nullptr)
                this->left->insert(n);
            else{
                this->left = n;
                n->parent = this;
            }
        }
        else{
            if (this->right != nullptr)
                this->right->insert(n);
            else {
                this->right = n;
                n->parent = this;
            }
        }
    }

    inline BSTNode<T>* get_node(auto x, auto y){
        if (x != nullptr && y == nullptr) return x;
        if (x == nullptr && y != nullptr) return y;
        return nullptr;
    }

    BSTNode<T>* delet(){
        if (this->left == nullptr || this->right == nullptr){
            if (this->parent->left == this){
                this->parent->left = get_node(this->left, this->right);
                if (this->parent->left != nullptr)
                    this->parent->left->parent = this->parent;
            }
            else {
                this->parent->right = get_node(this->left, this->right);
                if (this->parent->right != nullptr)
                    this->parent->right->parent = this->parent;
            }
            return this;
        }
        //case3 : this has 2 children
        else{
            BSTNode<T>* nl = this->nextLarger( );                                                                                                                                                                                                                                                                                                                                                                                                                                      
            BSTNode<T>* s = this;
            swap(nl, s);
            s->delet();
        }                                                                                                                                                                                                                                                                                                                                                                                                                                           
    }
};

// augumented bst node
template <typename T>
class MinBSTNode : BSTNode<T>
{
protected:
    MinBSTNode<T>* minNode = this;
public:
    
};


template <typename T>
class BSTree 
{
protected:
    BSTNode<T>* root = nullptr;
public:
    BSTree(){

    }
    ~BSTree(){

    }
    BSTNode<T>* find(T k){
        if (root == nullptr) return nullptr;
        return root->find(k);
    }
    BSTNode<T>* find_min(){
        if (root == nullptr) return nullptr;
        return root->findMin();
    }

    BSTNode<T>* next_larger(T x) {
        BSTNode<T>* n = root->find(x);
        return (root == nullptr)? nullptr : n->nextLarger();
    }
    BSTNode<T>* insert(T k){
        BSTNode<T> *n = new BSTNode<T>(k);
        if (root == nullptr) root = n;
        else root->insert(n);
        return n;
    }

    BSTNode<T>* delet(T k){
        BSTNode<T>* n = this->find(k);
        if (n == nullptr) return nullptr;
        if (n == root){
            BSTNode<T>* psudoNode;
            psudoNode->left = root;
            root->parent = psudoNode;
            BSTNode<T>* deleted = root->delet();
            root = psudoNode->left;
            if (root != nullptr)
                root->parent = nullptr;
            return deleted;
        }
        else{
            return n->delet();
        }
    }
};

template <typename T>
class AVLTree : public BSTree<T> {

public:
    int height(BSTNode<T>* x){ 
        if (x == nullptr) return -1;
        else return x->height; 
    }

    void update_height(BSTNode<T>* x) {
        x->height = max( height(x->left) , height(x->right) ) + 1;
    }

    void left_rotate (BSTNode<T>* x){
        BSTNode<T>* y = x->right;
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

    void right_rotate (BSTNode<T>* x){
        BSTNode<T>* y = x->left;
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

    void rebalance (BSTNode<T>* x){
        while (x) {
            update_height(x);
            if (height(x->left) + 2 <= height(x->right)){
                if (height(x->right->left) <= height(x->right->right))
                    left_rotate(x);
                else{
                    right_rotate(x->right);
                    left_rotate(x);
                }
            }
            else if ( height(x->right) + 2 <= height(x->left)){
                if (height(x->left->right) <= height(x->left->left))
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
        BSTNode<T>* n = BSTree<T>::insert(k);
        rebalance(n);
    }

    void delet(T k) {
        BSTNode<T>* n = BSTree<T>::delet(k);
        rebalance(n);
    }

};


int main()
{
    AVLTree<int> avltree;
    BSTree<int> bst;
    for (int i = 1; i < 9; i++){
        bst.insert(i);

        avltree.insert(i);
    }

    cout << bst.next_larger(6)->key << endl;
    // bst.
    for (int i = 2; i < 9; i++){
        bst.delet(i);
        avltree.delet(i);
    }
    
}