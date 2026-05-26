#ifndef PROCESS_H
#define PROCESS_H
#include <windows.h>
#include <cstdlib>
#include <string>
#include <memory>
#include "./Metadata/ProcessMetadata.h"

class Process
{
    private:
        bool running;
        DWORD processId;
        HANDLE processHandle;
        std::string processName;
        HANDLE getProcessHandle(void);
        std::string setProcessName(void);
        std::string parseName(std::string name);
        std::shared_ptr<ProcessMetadata> metadata;
    public:
        Process(void);
        Process(DWORD processId);
        bool kill(void);
        DWORD getProcessId(void);
        void deleteProcess(void);
        bool isRunning(void);
        std::string toString(void);
        void reset(DWORD processId);
        void setIsRunning(bool isRunning);
        std::string getProcessName(void);
        std::shared_ptr<ProcessMetadata> getMetadata(void) const;
};

inline DWORD Process::getProcessId(void) 
{
    return processId;
}

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

inline std::shared_ptr<ProcessMetadata> Process::getMetadata(void) const
{
    return metadata;
}

#endif