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
public:
    Node *root;
    int node_num;
    Btree(){
        node_num = 0;
        root = allocate_node();
        disk_write(root);
    }

    Node<T>* Btree_search(Node *x, T k, int* idx){
        int i = 1;
        while (i <= x->n && k < x->keys[i])
            i++;
        if (i < x->n && k == x->keys[i]){
            *idx = i;
            return x;
        }
        if (x->isLeaf) return nullptr;
        else {
            disk_read(x->ptrs[i]);
            int idx = -1;
            return Btree_search(x->ptrs[i], k, &idx);
        }
    }

    Node<T>* Btree_insert(T k){
        Node<T>*r = root;
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

    bool remove(T k){
        int idx = -1;
        if (Btree_search(root, k, &idx) == nullptr) return false;
        if (root->isLeaf && root->n == 1){
            recursive_clear(root);
            return true;
        }
        recursive_remove(root, k);
        return true;
    }

private:

    void Btree_split(Node *x, int i, Node<T>* y){
        // create z
        Node<T>* z = allocate_node();
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

    void Btree_insert_notfull(Node<T>* x, T k){
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

    void recursive_remove(Node *x, T k){
        int i = 1;
        while (i <= x->n && x->keys[i] < k) 
            i++;
        if (i <= x->n && x->keys[i] == k){ // in this node
            if (x->isLeaf){ // case 1
                for (int j = i; j <= x->n-1;j++)
                    x->keys[j] = x->keys[j+1];
                x->n--;
                return;
            }
            else{ //case 2, x is a internal node
                Node *c1 = x->ptrs[i];
                Node *c2 = x->ptrs[i+1];
                if (c1->n >= t){
                    T prev = get_predecessor(c1);
                    x->keys[i] = prev;
                    recursive_remove(c1, prev);
                    return;
                }
                else if (c2->n >= t){
                    T next = get_successor(c2);
                    x->keys[i] = next;
                    recursive_remove(c2, next);
                    return;
                }
                else {
                    merge_child(x, i);
                    recursive_remove(x->ptrs[i], k);
                }
            }
        } 
        else { // not in this node
            Node<T>* c = x->ptrs[i];
            Node<T>* c1 = (x->n >= 1) ? x->ptrs[i-1] : nullptr;
            Node<T>* c2 = (x->n <= 2*t-1) ? x->ptrs[i+1] : nullptr;
            if (x->ptrs[i]->n == t - 1){
                if (c1 && c1->n >= t){ // borrow from left silbing
                    for (int j = c->n; j >= 1; j++)
                        c->keys[j+1] == c->keys[j];
                    c->keys[1] = x->keys[i-1];
                    c->n++;
                    if (! c->isLeaf){
                        for (int j = c->n+1; j >= 1; j++)
                            c->ptrs[j+1] = c->ptrs[j];
                        c->ptrs[1] = c1->ptrs[c1->n+1];
                    }
                    x->keys[i-1] = c1->keys[c1->n];
                    c1->n--;
                }
                else if (c2 && c2->n >= t){
                    c->keys[c->n+1] = x->keys[i];
                    c->n++;
                    x->keys[i] = c2->keys[1];
                    c2->n--;
                    for (int j = 1; j < c2->n-1; j++)
                        c2->keys[j] = c2->keys[j+1];
                    if (! c2->isLeaf){
                        for (int j = 1; j < c2->n; j++)
                            c2->ptrs[j] = c2->ptrs[j+1];
                        c->ptrs[c->n+2] = c2->ptrs[1];
                    }
                }
                else if (c1) {
                    merge_child(x, i);
                    c = c1;  //always find the left
                }
                else if (c2) {
                    merge_child(x, i);
                }
            }
            recursive_remove(c, k);
        }
    }

    void merge_child(Node<T>* p, int idx){
        Node *c1 = p->ptrs[idx];
        Node *c2 = p->ptrs[idx+1]; // c1, c2 has n = t-1

        // copy c2 to c1, adjust c1
        c1->n = 2*t-1;
        c1->keys[t] = p->keys[idx];
        for (int i = 1; i <= t-1; i++)
            c1->keys[i+t] = c2->keys[i];
        for (int i = 1; i <= t; i++)
            c1->ptrs[i+t] = c2->ptrs[i];

        // adjust p
        p->n--;
        for (int i = idx; i < p->n; i++){
            p->keys[i] = p->keys[i+1];
            p->ptrs[i+1] = p->ptrs[i+2];
        }
        delete_node(c2);
        // special case: root node
        if (p->n == 0){
            if (p == root) root = c1;
            delete_node(p);
        }
    }

    // Node x is a previous node
    T get_predecessor(Node<T>* x){
        while (! x->isLeaf)
            x = x->ptrs[x->n+1];
        return x->keys[x->n];
    }
    T get_successor(Node<T>* x){
        while (! x->isLeaf)
            x = x->ptrs[1];
        return x->keys[1];
    }

    void delete_node(Node<T>* R){
        //TODO delete keys, ptrs[]
        delete R;
        node_num--;
        R = nullptr;
    }
    void recursive_clear(Node<T>* R){
        if (R == nullptr) return;
        if (! R->isLeaf){
            for (int i = 1; i <= R->n + 1; i++)
                recursive_clear( R->ptrs[i] );
        }
        delete_node(R);
    }

    Node<T>* allocate_node(){
        Node<T>* node = new Node();
        node_num++;
        return node;
    }
    void* disk_read(Node<T>* node){
#ifdef DEBUG
        cout << "read " << node << endl;
#endif
    }
    void* disk_write(Node<T>* node){
#ifdef DEBUG
        cout << "write " << node << endl;
#endif
    }

};

int main()
{
    Btree<int> btree;
    for (int i = 0; i < 20; i++){
        int x = rand() % 2079999;
        // cout << "n = " << i  << "x: " << x << endl;
        cout << "node num" <<  btree.node_num << endl;
        btree.Btree_insert(x);
    }
    for (int i = 19; i >= 10; i--){
        // cout << "node num: " <<  btree.node_num << endl;
        btree.remove(i);
    }

    return 0;
}