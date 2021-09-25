#ifndef TRIE_TREE_H
#define TRIE_TREE_H

#include "use.h"
class Key;
class Record;

const int num_char = 28;

struct Trie_node {
    Record *data;
    Trie_node* branches[num_char];
};

class Trie_tree{
public:
    Trie_node* root;
    Error_code tree_search(const Key &target, Record &x) const;
    Error_code insert(const Record &x);
};




#endif