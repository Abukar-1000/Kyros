#ifndef PROCESS_H
#define PROCESS_H
#include <windows.h>
#include <cstdlib>
#include <string>

class Process
{
    private:
        /* data */
        bool running;
        DWORD processId;
        HANDLE processHandle;
        std::string processName;
        HANDLE getProcessHandle(void);
        std::string setProcessName(void);
        std::string parseName(std::string name);
    public:
        Process(void);
        Process(DWORD processId);
        bool kill(void);
        DWORD getProcessId(void);
        void deleteProcess(void);
        std::string toString(void);
        bool isRunning(void);
        void setIsRunning(bool isRunning);
        std::string getProcessName(void);
};


inline bool Process::isRunning(void) 
{
    return running;
}

inline void Process::setIsRunning(bool isRunning) 
{
    this->running = isRunning;
}

inline std::string Process::getProcessName(void)
{
    return processName;
}

inline std::string Process::toString()
{
    return "[" + std::to_string(processId) + "] => " + processName;
}

#endif