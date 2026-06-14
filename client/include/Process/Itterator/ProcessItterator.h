#ifndef PROCESS_ITTERATOR_H
#define PROCESS_ITTERATOR_H
#include <iostream>
#include <windows.h>
#include <Psapi.h>
#include <string>
#include <vector>

class ProcessItterator
{
    private:
        size_t processCount;
        std::vector<DWORD> processIds;
        DWORD currentIndex;
        bool checkBounds();
        bool captureProcessIds();
    public:
        ProcessItterator();
        ProcessItterator(size_t processCount);
        bool contains(DWORD processId);
        bool hasNext();
        DWORD current();
        DWORD next();
        void reset();
};

#endif // PROCESS_ITTERATOR_H