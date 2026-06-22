#include <iostream>
#include <vector>
#include <cstddef>
#include "./include/Process/Context/ProcessContext.h"
#include "./include/Process/Observer/ProcessObserver.h"
#include "./include/Process/Itterator/ProcessItterator.h"
#include "./include/State/InterProcessCom/Pipe/Pipe.h"
#include "./include/State/InterProcessCom/PipeBuilder/PipeBuilder.h"
#include "./include/State/BinaryBuilder/BinaryBuilder.h"
#include "./include/Process/Process.h"
#include "./include/Command/Process/DeleteCommand.h"
#include "./include/Command/Visitors/ProcessVisitor.h"
#include "./include/BGWorker/Command/CommandWorker.h"
#include "./include/BGWorker/Context/BGWorkerContext.h"
#include "./include/BGWorker/Context/BGWorkerContextSingleton.h"
#include "./include/BGWorker/Gateway/GatewayWorker.h"

struct ProcessInfo
{
    uint32_t processId;
    char processName[256];
};

int main() {
    DWORD time = 50000;
    std::cout << "Hello, World! Kyros" << std::endl;
    
    auto gatewayWorker = GatewayWorker();
    gatewayWorker.start();
    gatewayWorker.join();
    Sleep(time * 1000);
    return 0;
}