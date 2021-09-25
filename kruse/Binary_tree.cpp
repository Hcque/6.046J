#include "Binary_tree.h"
#include <cstddef>
#include <iostream>

using namespace std;

template <class Entry>
Binary_tree<Entry>::Binary_tree(){ root = NULL; }

template <class Entry>
bool Binary_tree<Entry>::empty() const { return root == NULL; }

template <class Entry>
void Binary_tree<Entry>::inorder( void (*visit)(Entry&)){
    recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry>* sub_root, void(*visit)(Entry&)){
    if (sub_root != NULL){
        recursive_inorder(sub_root->left, visit);
        (*visit)(sub_root->data);
        recursive_inorder(sub_root->right, visit);
    }
}

// 2 way
template <class Record>
Binary_node<Record>*  Search_tree<Record>:: search_for_node(
    Binary_node<Record>* sub_root, Record &target) const
{
    if (sub_root == NULL || sub_root->data == target) return sub_root;
    else if (target < sub_root->data) 
        return search_for_node(sub_root->left, target);
    else return search_for_node(sub_root->right, target);
}

// template <class Record>
// Binary_node<Record>*  Search_tree<Record>:: search_for_node(
//     Binary_node<Record>* sub_root, Record &target) const
// {
//     while (sub_root != NULL && sub_root->data != target){
//         if (target < sub_root->data) sub_root = sub_root->left;
//         else sub_root = sub_root->right;
//     }
//     return sub_root;
// }

template <class Record>
Error_code Search_tree<Record>::tree_search(Record &target) const{
    
}

int main()
{
    // cout << "A" << endl;
    return 0;
}