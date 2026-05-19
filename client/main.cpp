#include <iostream>
#include "./include/ProcessItterator/ProcessItterator.h"

int main() {
    std::cout << "Hello, World! Kyros" << std::endl;
    auto processItterator = ProcessItterator();
    while (processItterator.hasNext())
    {
        std::cout << "Process ID: " << processItterator.current() << std::endl;
        processItterator.next();
    }
    
    return 0;
}