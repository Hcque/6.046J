#include <iostream>
#include <cassert>

using namespace std;


template <class Node_entry>
struct Node{
    Node_entry entry;
    Node<Node_entry> *next;
    Node<Node_entry> *prev;
    Node(){}
    Node(Node_entry x, 
        Node<Node_entry> *link_back = NULL,
        Node<Node_entry> *link_next = NULL ) : entry(x), prev(link_back), next(link_next) {}
};

template <class List_entry>
class List{
public:
    List();
    List(const List<List_entry>& copy);
    void operator=(const List<List_entry>& copy);

    ~List();
    void clear();
    int size() const;
    bool empty() const;
    void replace(int pos, const List_entry& x);
    void retrieve(int pos, List_entry& x) const;
    void remove(int pos, List_entry& x);
    void insert(int pos, const List_entry& x);
    void traversal(void (*visit)(List_entry& x));
    //

protected:
    int count;
    mutable int cur_pos;
    mutable Node<List_entry> *cur;

    void set_pos(int position) const;
};

template <class List_entry>
List<List_entry>:: List() : count(0), cur_pos(-1), cur(0) {}

template <class List_entry>
List<List_entry>:: List(const List<List_entry>& copy)
{
    
    count = copy.count;
    cur_pos = copy.cur_pos;
    if (cur_pos == 0) cur = 0;
    else{
        Node<List_entry> * oldN, *newN;
        oldN = copy.cur;
        newN = cur = new Node<List_entry>(oldN->entry);

        while (oldN->next){
            oldN = oldN->next;
            newN->next = new Node<List_entry>(oldN->entry, newN, 0);
            newN = newN->next;
        }
        oldN = copy.cur;
        newN = cur;
        while (oldN->prev){
            oldN = oldN->prev;
            newN->prev = new Node<List_entry>(oldN->entry, 0, newN);
            newN = newN->prev;
        }
        newN = oldN = 0;
    }
}


template <class List_entry>
void List<List_entry>:: set_pos(int position) const
{
    if (position < 0 || position >= count) {
        cout << "RANGE!" << endl;
        return;
    }
    if (position < cur_pos){
        while (cur_pos != position) {
            cur = cur->prev; cur_pos--;
        }
    }
    else{
        while (cur_pos != position) {
            cur = cur->next; cur_pos++;
        }
    }

}
template <class List_entry>
void List<List_entry>:: operator=(const List<List_entry>& copy)
{
    List<List_entry> newL(copy);
    clear();
    count = newL.count;
    cur_pos = newL.cur_pos;
    cur = newL.cur;
    newL.cur = 0;

}

template <class List_entry>
void List<List_entry>:: clear()
{
    Node<List_entry> *p, *q;
    if (cur == 0) return;
    for (p = cur->prev; p; p=q)
    {
        q = p->prev;
        delete p; p = 0;
    }

    for (p = cur; p; p=q)
    {
        q = p->next;
        delete p; p = 0;
    }

    // p = cur;
    // delete p;
    cur = 0;
    count = 0;
    cur_pos = -1;
}

template <class List_entry>
List<List_entry>:: ~List()
{
    clear();
    cur_pos = -1;
    count = 0;
}


template <class List_entry>
void List<List_entry>:: retrieve(int pos, List_entry& x) const
{
    if (pos < 0 || pos >= count) {
        cout << "retr!" << endl;
        return;
    }
    set_pos(pos);
    x = cur->entry;
}


template <class List_entry>
void List<List_entry>:: replace(int pos, const List_entry& x)
{
    if (pos < 0 || pos >= count) return;
    set_pos(pos);
    cur->entry = x;
}

template <class List_entry>
void List<List_entry>:: remove(int pos,  List_entry& x) 
{
    if (pos < 0 || pos >= count) return;
    if (count == 0) return;
    Node<List_entry> *oldN;
    
    set_pos(pos);
    oldN = cur;
    if (cur->prev) cur->prev->next = cur->next;
    if (cur->next) {
        cur->next->prev = cur->prev;
        cur = cur->next;
    }
    else{
        cur = cur->prev; pos--;
    }

    x = oldN->entry;
    count--;
    delete oldN;
}

template <class List_entry>
void List<List_entry>:: insert(int pos, const List_entry& x)
{
    if (pos < 0 || pos > count) {
        cout << "insert!" << endl;
        return;
    }
    Node<List_entry> *prece, *follow, *newN;
    if (pos == 0)
    {
        if (count == 0) follow = 0;
        else{
            set_pos(pos); follow = cur;
        }
        prece = 0;
    }
    else{
        set_pos(pos-1);
        prece = cur; follow = prece->next;
    }
    newN = new Node<List_entry>(x,prece, follow);
    if (prece) prece->next = newN;
    if (follow) follow->prev = newN;

    cur = newN; newN = 0;
    assert(cur!=0);
    cur_pos++;
    count++;
}

template <class List_entry>
int List<List_entry>:: size()  const
{
    return count;
}
template <class List_entry>
void List<List_entry>:: traversal(void (*visit) (List_entry& x)) 
{
    cout << "in traversal "<< endl;
    Node<List_entry>* p;
    p = cur;
    if (cur == 0) return;
    while (p->prev) p = p->prev;
    for (;p;p=p->next) {
        // cout << p->entry << endl;
        (*visit)(p->entry);
    }
}

int n;

void v(int& x){
    // cout << "in v" << endl;
    cout << x << endl;
}

int main()
{
    List<int> LL;
    cin >> n;

    int nn;
    LL.insert(0, 92);
    // LL.retrieve(0,nn);
    // cout << nn << endl;
    // LL.traversal(v);

    for (int i = 1; i <= n; i++) {
        LL.insert(i, i);
        LL.retrieve(i, nn);
        cout << nn << endl;
    }
    for (int i = 0; i < n/2; i++) {
        LL.insert(i+1, 2*i);
    }
    // LL.traversal(v);

    List<int> LL2(LL);
    List<int> LL3 = LL;

    LL2.traversal(v);
    LL3.traversal(v);
    while (LL.size()) LL.remove(0,nn);
    LL.traversal(v);



}

/*
10
R 7
D 1
L 3
IL 2 10
D 3
IL 2 7
L 8
R 9
IL 4 7
IR 2 2
*/
