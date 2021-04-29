template<class T>
class Btree
{
private:
    static const int = 3;
    struct Node {
        bool isLeaf;
        int n;
        T key_value[t];
        Node *p_child[t];
    }
    Node *root
public:


private:
    Node* allocate_node(){
        Node* node = new Node();
        return node;
    }
    void* disk_read(Node* node){
        cout << "read" << node << endl;
    }
    void* disk_write(Node* node){
        cout << "write" << node << endl;
    }

}