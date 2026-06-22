#ifndef COMMAND_CONTEXT_H
#define COMMAND_CONTEXT_H
#include <memory>
#include <unordered_map>
#include <algorithm>
#include "../../Process/Itterator/ProcessItterator.h"
#include "../../Process/Process.h"

using ProcessMap = std::unordered_map<DWORD, Process>;
class CommandContext
{
    private:
        size_t processCount;
        void configureCurrProcesses(void);
    public:
        CommandContext();
        CommandContext(size_t processCount);
        ~CommandContext() = default;
        std::shared_ptr<ProcessItterator> processItterator;
        std::shared_ptr<ProcessMap> processMap;
        void markAndSweep(void);
};

#endif // COMMAND_CONTEXT_H