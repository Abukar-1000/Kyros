#include "../../../include/Command/Context/CommandContext.h"

CommandContext::CommandContext()
:   processItterator(std::make_shared<ProcessItterator>()),
    processMap(std::make_shared<ProcessMap>()),
    processCount(1024)
{
    this->processMap->reserve(1024);
    this->configureCurrProcesses();
}

CommandContext::CommandContext(size_t processCount)
:   processItterator(std::make_shared<ProcessItterator>()),
    processMap(std::make_shared<ProcessMap>()),
    processCount(processCount)
{
    this->processMap->reserve(processCount);
    this->configureCurrProcesses();
}

void CommandContext::configureCurrProcesses(void)
{
    this->processItterator->reset();
    for (size_t i = 0; processItterator->hasNext(); i++)
    {
        Process process(processItterator->current());
        this->processMap->insert({
            process.getProcessId(),
            process
        });
        processItterator->next();
    }
}

void CommandContext::markAndSweep(void)
{
    std::erase_if(*this->processMap, [this](const auto& pair) {
        DWORD processId = pair.first;
        Process process = pair.second;
        return (
            !process.isRunning() || 
            !this->processItterator->contains(processId)
        );
    });

    this->processItterator->reset();
    ProcessMap freshMap;
    while (processItterator->hasNext())
    {
        DWORD processId = processItterator->current();
        auto it = this->processMap->find(processId);
        if (it != this->processMap->end())
        {
            if (it->second.isRunning())
            {
                this->processMap->insert({
                    processId,
                    it->second
                });
            }
        }
        else
        {
            Process process(processId);
            if (process.isRunning())
            {
                Process process(processId);
                this->processMap->insert({
                    processId,
                    process
                });
            }
        }
        processItterator->next();
    }
}