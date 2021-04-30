#include <iostream>
using namespace std;
// #define DEBUG 1


template<class T>
class Btree
{
private:
    static const int t = 3;
    struct Node {
        bool isLeaf;
        int n;
        T keys[2*t]; // notice 1 is the first elem
        Node *ptrs[2*t+1]; 
        Node(): isLeaf(true), n(0){}
    };
    Node *root;
    int node_num;
public:
    Btree(){
        node_num = 0;
        root = allocate_node();
        disk_write(root);
    }

    Node* Btree_search(Node *x, T k, int* idx){
        int i = 1;
        while (i <= x->n && k < x->keys[i])
            i++;
        if (i < x->n && k == x->keyj[i]){
            *idx = i;
            return x;
        }
        if (x->isLeaf) return nullptr;
        else {
            disk_read(x->ptrs[i]);
            return Btree_search(x->ptrs[i], k);
        }
    }

    Node* Btree_insert(T k){
        Node*r = root;
        if (r->n == 2*t-1){
            Node *s = allocate_node();
            s->n = 0;
            s->isLeaf = false;
            s->ptrs[1] = r;
            root = s;
            Btree_split(s, 1, r);
            Btree_insert_notfull(s, k);
        }
        else
            Btree_insert_notfull(r, k);
    }

    bool remove(Node* x, T k){
        int idx;
        if (Btree_search(x, k, &idx) == nullptr) return false;
        if (x == root && x->n == 1){
            recursive_clear(x);
            return true;
        }
        return recursive_remove(x, k);
    }

private:

    void Btree_split(Node *x, int i, Node* y){
        // create z
        Node* z = allocate_node();
        z->n = t - 1;
        z->isLeaf = y->isLeaf;
        for (int j = 1; j <= t-1; j++) 
            z->keys[j] = y->keys[j+t];
        if (! z->isLeaf){
            for (int j = 1; j <= t; j++)
              z->ptrs[j] = y->ptrs[j+t];
        }
        
        // adjust y
        y->n = t-1;
        // adjust x to add one key and ptr
        for (int j = x->n+1; j >= i+1; j--) 
            x->ptrs[j+1] = x->ptrs[j];
        x->ptrs[i+1] = z;
        for (int j = x->n; j >= i; j--)
            x->keys[j+1] = x->keys[j];
        x->keys[i] = y->keys[t]; 
        x->n++;
        disk_write(x);
        disk_write(y);
        disk_write(z);
    }

    void Btree_insert_notfull(Node* x, T k){
        int i = x->n;
        if (x->isLeaf){
            while (i >= 1 && x->keys[i] > k){
                x->keys[i+1] = x->keys[i];
                i--;
            }
            x->keys[i+1] = k;
            x->n++;
            disk_write(x);
        } else{
            while (i >= 1 && x->keys[i] > k)
                i--;
            i++;
            disk_read(x->ptrs[i]);
            if (x->ptrs[i]->n == 2*t-1){
                // full child
                Btree_split(x, i, x->ptrs[i]);
                if (x->keys[i] < k) i++;
            }
            Btree_insert_notfull(x->ptrs[i], k);
        }
    }

    bool recursive_remove(Node *x, T k){

    }

    // Node x is a previous node
    T get_predecessor(Node* x){
        if (! x == nullptr){
            while (! x->isLeaf)
                x = x->ptrs[x->n+1];
            return x->keys[x->n];
        }
    }
    T get_successor(Node* x){
        if (! x == nullptr){
            while (! x->isLeaf)
                x = x->ptrs[1];
            return x->keys[1];
        }
    }

    void delete_node(Node* R){
        //TODO delete keys, ptrs[]
        delete R;
        R = nullptr;
    }
    void recursive_clear(Node* R){
        if (R == nullptr) return;
        if (! R->isLeaf){
            for (int i = 1; i <= R->n + 1; i++)
                recursive_clear( R->ptrs[i] );
        }
        delete_node(R);
    }

    Node* allocate_node(){
        Node* node = new Node();
        node_num++;
        return node;
    }
    void* disk_read(Node* node){
#ifdef DEBUG
        cout << "read " << node << endl;
#endif
    }
    void* disk_write(Node* node){
#ifdef DEBUG
        cout << "write " << node << endl;
#endif
    }

};

int main()
{
    Btree<int> btree;
    for (int i = 0; i < 200; i++){
        int x = rand() % 2079999;
        // cout << "n = " << i  << "x: " << x << endl;
        btree.Btree_insert(x);
    }
    return 0;
}