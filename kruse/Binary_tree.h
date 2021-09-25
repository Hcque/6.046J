#ifndef BINARY_TREE_H
#define BINARY_TREE_H

enum Error_code {success, duplicated};

template <class Entry>
struct Binary_node{
    Entry data;
    Binary_node<Entry> *left;
    Binary_node<Entry> *right;

    Binary_node();
    Binary_node(const Entry &x);
};


template <class Entry>
class Binary_tree
{
public:
    Binary_tree();
    ~Binary_tree();

    bool empty() const;
    void inorder( void (*visit)(Entry&));
    int size() const;
    int height() const;
    void clear();

private:
    void recursive_inorder(Binary_node<Entry>* sub_root, void(*visit)(Entry&));
protected:
    Binary_node<Entry>* root;
};


template <class Record>
class Search_tree : public Binary_tree<Record> {
public:
    Error_code insert(const Record &new_data);
    Error_code remove(const Record &old_data);
    Error_code tree_search(Record &target) const;
private:
    Binary_node<Record>* search_for_node(Binary_node<Record>* sub_root, Record &target) const;

};


#endif