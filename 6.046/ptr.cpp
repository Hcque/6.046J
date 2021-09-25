#include <iostream>
#include <memory>

using namespace std;

class E {
    public:
    E(){ cout << "C" << endl;}
    ~E(){ cout << "D" << endl;}

};
int main ()
{
        shared_ptr<E> p2 = make_shared<E>();
    {
        // unique_ptr<E> ptr(new E());
        unique_ptr<E> ptr = make_unique<E>();


    shared_ptr<E> p3 = p2;
    }


    return 0;
}