#include <future>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>


// static loadMesh(std::vector<Ref<int>>)
// {

// }


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

void printEntity(const E& e)
{
    std::cout << e.m_name << "|" << e.m_age << std::endl;
}


struct vector2{
    float x, y;
};

class String {
private:
    char* m_buffer;
    unsigned int m_size;
public:
    String(const char* string){
        m_size = strlen(string);
        m_buffer = new char[m_size]; 
        memcpy(m_buffer, string, m_size);

    }

    String(const String& other):
        m_size(other.m_size)
    {
        std::cout << "copy string " << other.m_buffer << std::endl;
        m_buffer = new char[m_size];
        memcpy(m_buffer, other.m_buffer, m_size);
    }
    ~String()
    {
        delete [] m_buffer;
    }

    char& operator[] (unsigned int index)
    {
        return m_buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);

};


std::ostream& operator <<(std::ostream& stream, const String& string)
{
    stream << string.m_buffer;
    return stream;
}

void printS(const String& string)
{
    String copy = string;

    std::cout << "print string " << string << std::endl;

}

int main()
{
#if 0
    std::string ss = "ch";
    // E a = std::string("ch");
    // E b = 3;

    printEntity(E("ch"));
    // printEntity(3);

    vector2 a = {2,3};
    vector2 b = a;

    vector2* A = new vector2;
    vector2* B = A;
    B->y = 3;
#endif

    String s = "we";
    String s2 = s;
    s2[1] = 'p';
    std::cout << s << std::endl;
    std::cout << s2 << std::endl;

    printS(s);
    printS(s2);

    return 0;
}

