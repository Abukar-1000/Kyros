#include "../../../include/Command/Context/CommandContext.h"

CommandContext::CommandContext()
:   processItterator(std::make_shared<ProcessItterator>()),
    processList(std::make_shared<ProcessList>()),
    processCount(1024)
{
    this->processList->reserve(1024);
    this->configureCurrProcesses();
}

CommandContext::CommandContext(size_t processCount)
:   processItterator(std::make_shared<ProcessItterator>()),
    processList(std::make_shared<ProcessList>()),
    processCount(processCount)
{
    this->processList->reserve(processCount);
    this->configureCurrProcesses();
}

void CommandContext::configureCurrProcesses(void)
{
    this->processItterator->reset();
    for (size_t i = 0; processItterator->hasNext(); i++)
    {
        Process process(processItterator->current());
        this->processList->push_back(process);
        processItterator->next();
    }
}