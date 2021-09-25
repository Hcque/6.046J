#include <iostream>

int& getValue(){ 
    static int i = 10;
    return i; 
    }


void setValue(std::string&& value)
{

}
int main()
{

    // int a = getValue();
    getValue() = 6;
    // const int& a = 10;
    
    std::string a = "a";
    std::string b = "b";
    // std::string full = a + b;

    // std::cout << full << std::endl;

    setValue(a);
    setValue("aa");


    // std::cout << i << std::endl;

    double d = 9;
    int ii = static_cast<int>(d);
    std::cout << ii << std::endl;
    return 0;
}