#include "Trie_tree.h"


Error_code Trie_tree::tree_search(const Key &target, Record &x) const
{
    int pos = 0;
    char next_char;
    Trie_node* location = root;
    while (location != NULL && (target.get(next_char)) != ' ' ){
        location = location->branches[next_char];
        pos++;
    }
    if (location != NULL && location->data != NULL){
        x = *(location->data);
        return success;
    }
    else return not_present;
}
Error_code Trie_tree::insert(const Record &x)
{
    int pos = 0;
    char next_char;
    Trie_node* location = root;
    while (location != NULL && (x.get(next_char)) != ' ' ){
        int next_pos = atoi(next_char);
        if (location->branches[next_pos] == NULL)
            location->branches[next_pos] = new Trie_node();
        location = location->branches[next_char];
        pos++;
    }
    if (location->data != NULL) return duplicated;
    location->data = new Record(x);
    return success;
}