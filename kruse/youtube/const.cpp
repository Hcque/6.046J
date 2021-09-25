#include <iostream>
using namespace std;


class E
{
public:
    std::string m_name;
    int m_age;

    explicit E(const std::string& name):
        m_name(name), m_age(-1) {}
    explicit E(int a):   
        m_name("Unknown"), m_age(a) {}
};


int main()
{

    E *e = new E("we");

    const int MAXAGE = 90;
    const int *i = new int;
    i = &MAXAGE;
    cout << *i << endl;
    // *i = 9;
    
}