#include "../../include/Process/Context/ProcessContext.h"

ProcessContext::ProcessContext()
:   maxObserverCount(1024),
    currProcesses(std::make_shared<std::vector<Process>>())
{
    this->observers.reserve(1024);
    this->currProcesses->reserve(1024);
    this->configureCurrProcesses();
}

ProcessContext::ProcessContext(size_t maxObserverCount)
:   maxObserverCount(maxObserverCount),
    currProcesses(std::make_shared<std::vector<Process>>())
{
    this->observers.reserve(maxObserverCount);
    this->currProcesses->reserve(maxObserverCount);
    this->configureCurrProcesses();
}

void ProcessContext::configureCurrProcesses(void)
{
    this->processItterator.reset();
    for (size_t i = 0; processItterator.hasNext(); i++)
    {
        Process process(processItterator.current());
        this->currProcesses->push_back(process);
        processItterator.next();
    }
}

void ProcessContext::markCurrProcesses(void)
{
    this->processItterator.reset();
    for (size_t i = 0; processItterator.hasNext(); i++)
    {
        this->currProcesses->at(i).reset(processItterator.current());
        processItterator.next();
    }
}

void ProcessContext::notify()
{
    for (auto& observer : observers)
    {
        observer->update(this->currProcesses);
    }
} 

void ProcessContext::attach(std::shared_ptr<IObserver<SharedProcessList>> observer)
{
    observers.push_back(observer);
}

size_t ProcessContext::findObserverIndex(std::shared_ptr<IObserver<SharedProcessList>> observer)
{
    for (size_t i = 0; i < observers.size(); i++)
    {
        if (observers[i] == observer)
        {
            return i;
        }
    }

    return NULL;
}

void ProcessContext::detach(std::shared_ptr<IObserver<SharedProcessList>> observer)
{
    size_t index = this->findObserverIndex(observer);
    if (index == NULL)
    {
        return;
    }

    observers.erase(observers.begin() + index);
}

bool ProcessContext::killProcess(std::string processName)
{
    for (size_t i = 0; i < currProcesses->size(); i++)
    {
        auto process = currProcesses->at(i);
        if (process.getProcessName() == processName)
        {
            return process.kill();
        }
    }

    return false;
}

/**
 * @brief Likely to be deprecated in the future, this function moves all dead processes to the end of the list.
 * 
 */
void ProcessContext::moveDeadProcessesToEnd()
{
    size_t left = 0;
    this->endIndex = currProcesses->size() - 1;
    bool isUnderflow = this->endIndex > this->currProcesses->size();
    
    if (isUnderflow)
    {
        return;
    }

    while (left < this->endIndex)
    {
        if (!currProcesses->at(left).isRunning())
        {
            std::swap(currProcesses->at(left), currProcesses->at(endIndex));
            endIndex--;
            continue;
        } 

        left++;
    }
}