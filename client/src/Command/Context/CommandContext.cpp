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

void CommandContext::markAndSweep(void)
{
    this->processItterator->reset();
    size_t i = 0;

    while (processItterator->hasNext())
    {
        if (i >= this->processList->size())
        {
            this->processList->push_back(Process(processItterator->current()));
        }
        else if (this->processList->at(i).getProcessId() != processItterator->current())
        {
            this->processList->at(i).reset(processItterator->current());
        }

        processItterator->next();
        ++i;
    }

    if (this->processList->size() > i)
    {
        this->processList->resize(i);
    }
}