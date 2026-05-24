#include "../../include/Process/Itterator/ProcessItterator.h"

ProcessItterator::ProcessItterator() 
:   processCount(1024), 
    currentIndex(0) 
{
    processIds.resize(1024);
    this->captureProcessIds();
}

ProcessItterator::ProcessItterator(size_t processCount) 
:   processCount(processCount), 
    currentIndex(0) 
{
    processIds.resize(processCount);
    this->captureProcessIds();
}

bool ProcessItterator::hasNext() 
{
    return currentIndex < processCount;
}

bool ProcessItterator::checkBounds() 
{
    if (currentIndex >= processCount) {
        std::cout << "Process Itterator index out of bounds. Current index: "
                 << std::to_string(currentIndex) 
                 << ", Process count: " << std::to_string(processCount) 
                 << std::endl;
        return false;
    }

    return true;
}

DWORD ProcessItterator::current() 
{
    auto result = this->checkBounds();
    if (!result) {
        return 0;
    }

    return processIds[currentIndex];
}

DWORD ProcessItterator::next() 
{
    auto result = this->checkBounds();
    if (!result) {
        return 0;
    }

    currentIndex++;
    return processIds[currentIndex];
}

bool ProcessItterator::captureProcessIds() 
{
    DWORD bytesReturned = 0;
    bool captured = EnumProcesses(processIds.data(), processIds.size() * sizeof(DWORD), &bytesReturned);
    if (!captured) {
        std::cout << "Failed to capture process IDs. Error code: " << GetLastError() << std::endl;
    }

    processCount = bytesReturned / sizeof(DWORD);
    return captured;
}

void ProcessItterator::reset() 
{
    currentIndex = 0;
    this->captureProcessIds();
}