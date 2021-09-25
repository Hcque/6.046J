#include <iostream>
#include <string>
#include <algorithm>
#include <memory>


namespace apple
{
    void Print(const std::string& text){
        std::cout << text << std::endl;
    }

}

namespace orange
{
    void Print(const char* text){
        std::string temp = text;
        std::reverse(temp.begin(), temp.end());
        std::cout << temp << std::endl;
    }

}

using namespace apple;
using namespace orange;


struct AllocationMetric
{
    uint32_t totalAllocated = 0;
    uint32_t totalFreed = 0;

    uint32_t currentUsage() { return totalAllocated - totalFreed; }
};

static AllocationMetric s_AllocationMetric;


// allocate
void* operator new (size_t size)
{
    std::cout << "allocate" << std::endl;
    s_AllocationMetric.totalAllocated += size;
    return malloc(size);
}
void operator delete (void *memory, size_t size)
{
    s_AllocationMetric.totalFreed += size;
    std::cout << "delete" << std::endl;
    free(memory);
}

static void memoryUsage()
{
    std::cout << "Memory usage:" << s_AllocationMetric.currentUsage() << "Bytes" << std::endl;
}

struct Object
{
    int x, y, z;
};


int main()
{

#if 1
    // Print("hello");
    std::string string = "chorn";
    char * arr[8];
    memoryUsage();
    {
    memoryUsage();
    std::unique_ptr<Object> o = std::make_unique<Object>();
    memoryUsage();
    }
    memoryUsage();

#endif

    return 0;
}