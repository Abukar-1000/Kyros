#include <iostream>
#include <vector>
#include "./include/ProcessItterator/ProcessItterator.h"
#include "./include/Process/Process.h"

int main() {
    std::cout << "Hello, World! Kyros" << std::endl;
    const size_t processCount = 1024;
    std::vector<Process> processes(processCount);

    auto processItterator = ProcessItterator();
    while (processItterator.hasNext())
    {
        Process process(processItterator.current());
        std::cout << process.toString() << std::endl;
        processes.push_back(process);
        processItterator.next();
    }
    
    bool searching = true;
    std::string targetProcess = "Discord";
    while (searching)
    {
        for (Process& process : processes)
        {
            if (process.getProcessName().find(targetProcess) != std::string::npos)
            {
                std::cout << "Killing process: " << process.toString() << std::endl;
                process.kill();
            }
        }
        
        Sleep(1000);
    }
    return 0;
}