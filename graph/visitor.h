#include <iostream>
#include <vector>


template <typename T>
class Visitor{
public: 
    virtual bool operator() (T& e ) = 0;
};

template <typename T>
class NilVisitor: public Visitor<T>{
public: 
    virtual bool operator() (T& e ) {}
};

template <typename T>
class PrintVisitor: public Visitor<T>{
public: 
    virtual bool operator() (T& e ) {
        cout << e << " ";
    }
};
