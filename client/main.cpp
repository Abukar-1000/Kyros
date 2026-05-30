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

struct ProcessInfo
{
    uint32_t processId;
    char processName[256];
};

int main() {
    std::cout << "Hello, World! Kyros" << std::endl;
    auto context = BGWorkerContextSingleton::get();
    auto commandWorker = CommandWorker();
    commandWorker.join();
    commandWorker.start();

    Sleep(30 * 1000);

    std::cout << "\nPausing...\n" << std::endl;
    context->commandParams->paused = true;
    
    Sleep(10 * 1000);
    std::cout << "\nDisabling Pausing...\n" << std::endl;
    context->commandParams->paused = false;
    Sleep(10 * 1000);

    commandWorker.stop();
    Sleep(3 * 1000);
    return 0;
}