#include <iostream>
#include <vector>
#include "./include/Process/Context/ProcessContext.h"
#include "./include/Process/Observer/ProcessObserver.h"
#include "./include/Process/Itterator/ProcessItterator.h"
#include "./include/State/InterProcessCom/Pipe/Pipe.h"
#include "./include/State/InterProcessCom/PipeBuilder/PipeBuilder.h"
#include "./include/State/BinaryBuilder/BinaryBuilder.h"
#include "./include/Process/Process.h"
#include <cstddef>

struct ProcessInfo
{
    uint32_t processId;
    char processName[256];
};

int main() {
    std::cout << "Hello, World! Kyros" << std::endl;
    
    auto pContext = ProcessContext();
    auto pObserver = std::make_shared<ProcessObserver>();
    pContext.attach(pObserver);
    pContext.markCurrProcesses();
    pContext.notify();
    pContext.detach(pObserver);
    
    return 0;
}