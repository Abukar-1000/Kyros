#include <iostream>
#include <vector>
#include "./include/Process/Context/ProcessContext.h"
#include "./include/Process/Observer/ProcessObserver.h"
#include "./include/Process/Itterator/ProcessItterator.h"
#include "./include/Process/Process.h"

int main() {
    std::cout << "Hello, World! Kyros" << std::endl;
    auto pContext = ProcessContext();
    auto pObserver = std::make_shared<ProcessObserver>();
    pContext.attach(pObserver);
    pContext.markCurrProcesses();
    pContext.notify();
    pContext.detach(pObserver);
    std::cout << "Detached observer. No updates should be received." << std::endl;
    return 0;
}