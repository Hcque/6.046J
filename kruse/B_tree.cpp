#include <cstddef>
using namespace std;

enum Error_code{not_present, duplicated, success, overflow};

template <class Record, int order>
struct B_node{
    int count;
    Record data[order-1];
    B_node<Record, order>* branch[order];
};


template <class Record, int order>
class B_tree{
public:
    Error_code search_tree(Record& target);
    Error_code insert( const Record& new_entry);

    Error_code remove(const Record& target);

private:
    // ---------------- helper for search ---------------------
    Error_code recursive_search_tree(
        B_node<Record, order>* current, Record& target);
    Error_code search_node(
        B_node<Record, order>* current, Record& target, int &position);

    // ---------------- helper for insert ---------------------

    Error_code push_down(
        B_node<Record, order> *current, const Record& new_entry,
        Record& median, B_node<Record, order>* &right_branch
    );

    void push_in(B_node<Record, order>*current, const Record& entry, 
                B_node<Record, order> *right_branch, int position);
    void split(
        B_node<Record, order> *current,
        const Record& extra_entry,
        B_node<Record, order>* extra_branch,
        int position,
        B_node<Record, order>* &right_half,
        Record &median
    );
    // ---------------- helper for remove ---------------------
    Error_code recursive_remove( B_node<Record, order> *current, const Record& target);
    void remove_data(B_node<Record, order>* current, int position);
    void copy_in_predecessor(B_node<Record, order>* current, int position);
    void restore(B_node<Record, order>* current, int position);
    void move_left(B_node<Record, order>* current, int position);
    void move_right(B_node<Record, order>* current, int position);
    void combine(B_node<Record, order>* current, int position);

    B_node<Record, order> *root;
};

template <class Record, int order>
Error_code B_tree<Record, order>::search_tree(Record& target)
{
    return recursive_search_tree(root, target);
}

template <class Record, int order>
Error_code B_tree<Record, order>::recursive_search_tree(B_node<Record, order>* current, Record& target)
{
    Error_code result = not_present;
    int position;
    if (current != NULL) {
        result = search_node(current, target, position);
        if (result == not_present)
            result = recursive_search_tree(current->branch[position], target);
        else
            target = current->data[position];
    }
    return result;
}

template <class Record, int order>
Error_code B_tree<Record, order>::search_node(
    B_node<Record, order>* current, Record& target, int &position)
{
    position = 0;
    while (position < current->count && current->data[position] < target)
        position++;
    if (position < current->count && current->data[position] == target)
        return success;
    else return not_present;
}        

template <class Record, int order>
Error_code B_tree<Record, order>::insert(const Record& new_entry)
{
    Record median;
    B_node<Record, order> *right_branch, *new_root;
    Error_code result = push_down(root, new_entry, median, right_branch);
    if (result == overflow){
        new_root = new B_node<Record, order>();
        new_root->count = 1;
        new_root->data[0] = median;
        new_root->branch[0] = root;
        new_root->branch[1] = right_branch;
        root = new_root;
        result = success;
    }
    return result;
}

template <class Record, int order>
Error_code B_tree<Record, order>::push_down(
    B_node<Record, order> *current, const Record& new_entry,
    Record& median, B_node<Record, order>* &right_branch)
{
    Error_code result;
    //  int position = 0;
    int *position = new int;
    if (current== NULL){
        median = new_entry;
        right_branch = NULL;
        result = overflow;
    }
    else {
        // if (0){
        if (search_node(current, new_entry, *position) == success){
            result = duplicated;
        }
        else {
            Record extra_entry;
            B_node<Record, order>* extra_branch;
           result = push_down(current->branch[position], new_entry, extra_entry, extra_branch); 
           if (result == overflow){
               if (current->count < order -1){
                   result = success;
                   push_in(current, extra_entry, extra_branch, position);
               }
               else {
                //    split();
               }
           }
        }
    }
    return result;
}

template <class Record, int order>
void B_tree<Record, order>::push_in(B_node<Record, order>*current, const Record& entry, 
            B_node<Record, order> *right_branch, int position)
{
    for (int i = current->count; i > position; i--){
        current->data[i] = current->data[i-1];
        current->branch[i+1] = current->branch[i];
    }
    current->data[position] = entry;
    current->branch[position+1] = right_branch;
    current->count++;
}

template <class Record, int order>
void B_tree<Record, order>::split(
    B_node<Record, order> * current,
    const Record& extra_entry,
    B_node<Record, order>* extra_branch,
    int position,
    B_node<Record, order>* &right_half,
    Record &median)
{
    right_half = new B_node<Record, order>;
    int mid = order/2;
    if (position <= mid){
        for (int i = mid; i < order-1; i++){
            right_half->data[i-mid] = current->data[i]; 
            right_half->branch[i+1-mid] = current->branch[i+1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(current, extra_entry, extra_branch, position);
    }
    else {
        mid++;
        for (int i = mid; i < order-1; i++){
            right_half->data[i-mid] = current->data[i]; 
            right_half->branch[i+1-mid] = current->branch[i+1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(current, extra_entry, extra_branch, position);
    }
    median = current->data[current->count-1];
    right_half->branch[0] = current->branch[current->count];
    current->count--;
}

// remove implementation
template <class Record, int order>
Error_code B_tree<Record, order>::remove(const Record& target)
{
    Error_code result = recursive_remove(root, target);
    if (root == NULL && root->count == 0){
        B_node<Record, order> old_root = root;
        root = root->branch[0];
        delete old_root;
    }
    return result;
}

template <class Record, int order>
Error_code B_tree<Record, order>::recursive_remove(B_node<Record, order>* current, const Record& target)
{
    Error_code result; int position;
    if (current == NULL) result = not_present;
    else{
        if (search_node(current, target, position) == success ){
            result = success;
            if (current->branch[position] != NULL){
                copy_in_predecessor(current, position);
                recursive_remove();
            }
            else remove_data(current->branch[position], target); // leaf
        }
    }
    return result;
}

template <class Record, int order>
void B_tree<Record, order>::remove_data(B_node<Record, order>* current, int position)
{
    for (int i = position; i < current->count-1; i++){
        current->data[i] = current->data[i+1];
    }
    current->count--;
}

template <class Record, int order>
void B_tree<Record, order>::copy_in_predecessor(B_node<Record, order>* current, int position)
{
    B_node<Record, order> *leaf = current->branch[position];
    while(leaf->branch[leaf->count] != NULL)
        leaf = leaf->branch[leaf->count];
    current->data[position] = leaf->data[leaf->count-1];
}

template <class Record, int order>
void B_tree<Record, order>::restore(B_node<Record, order>* current, int position)
{
    if (position == current->count){
        if (current->branch[position-1]->count < (order-1)/2)
            move_right(current, position-1);
        else combine(current, position);
    }
    else if (position == 0){
        if (current->branch[1]->count < (order-1)/2)
            move_left(current, 1);
        else combine(current, position);
    }
    else{
        if (current->branch[position-1]->count < (order-1)/2)
            move_right(current, position-1);
        else if (current->branch[position+1]->count < (order-1)/2)
            move_right(current, position+1);
        else combine(current, position);
    }
}

template <class Record, int order>
void B_tree<Record, order>::move_left(B_node<Record, order>* current, int position)
{
}

template <class Record, int order>
void B_tree<Record, order>::move_right(B_node<Record, order>* current, int position)
{
}

template <class Record, int order>
void B_tree<Record, order>::combine(B_node<Record, order>* current, int position)
{
}

int main()
{
    B_tree<int, 5> B;
    int *i = new int;
    *i = 9;
    B.insert(*i);
    

    return 0;
}