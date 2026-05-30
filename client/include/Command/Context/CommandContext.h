#ifndef COMMAND_CONTEXT_H
#define COMMAND_CONTEXT_H
#include <memory>
#include <vector>
#include "../../Process/Itterator/ProcessItterator.h"
#include "../../Process/Process.h"

using ProcessList = std::vector<Process>;
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
        std::shared_ptr<ProcessList> processList;
        void markAndSweep(void);
};

#endif // COMMAND_CONTEXT_H