#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
using namespace std;


void H(){
    cout << "Hello" << endl;
}

void func(const vector<int> &vec, const function<void(int)>& f)
{
    for (int v : vec)
        f(v);
}

template <class T>
void Print(T v){
    cout << v << endl;
}

template <typename T, int size>
class Array
{
    T array[size];

};
int main()
{

    // auto f = &H;
    // auto f2 = H;

    // cout << f << " | " << f2 << endl;
    typedef void (*Name)();
    Name f = H;
    f();
    f();
    // -------------------------------

    vector<int> values = {3,5,2,1,2};
    auto it = find_if(values.begin(), values.end(), [](int v){ return v > 3; } );
    // cout << *it << endl;

    int a = 5;
    auto lambda = [a](int v) mutable {  a = 6; cout << v << a << endl;};

    func(values, lambda);

    Print(3);
    Print("value");

    Array<int, 6> array;



    using scoreMap = unordered_map<string, int>;
    // using scoreMapIt = scoreMap::const_iterator;
    scoreMap map;
    map["A"] = 1;
    map["B"] = 2;

    for (scoreMap::const_iterator it = map.begin(); it != map.end(); ++it)
    {
        auto &key = it->first;
        auto &value = it->second;
        cout << key << "|" << value << endl;
    }
    for (auto it: map){

        auto &key = it.first;
        auto &value = it.second;
        cout << key << "|" << value << endl;
    }
    cin.get();



    return 0;
}