#ifndef PROCESS_CONTEXT_H
#define PROCESS_CONTEXT_H
#include <windows.h>
#include <vector>
#include <memory>
#include "../../State/Subject/ISubject.h"
#include "../../State/Observer/IObserver.h"
#include "../Itterator/ProcessItterator.h"
#include "../Process.h"
using SharedProcessList = std::shared_ptr<std::vector<Process>>;

class ProcessContext: public ISubject<SharedProcessList>
{
    private:
        size_t maxObserverCount;
        SharedProcessList currProcesses;
        ProcessItterator processItterator;
        std::vector<std::shared_ptr<IObserver<SharedProcessList>>> observers;
        size_t findObserverIndex(std::shared_ptr<IObserver<SharedProcessList>> observer);
        void configureCurrProcesses(void);
    public:
        ProcessContext();
        ~ProcessContext() = default;
        ProcessContext(size_t maxObserverCount);
        void attach(std::shared_ptr<IObserver<SharedProcessList>> observer) override;
        void detach(std::shared_ptr<IObserver<SharedProcessList>> observer) override;
        void markCurrProcesses(void);
        void notify() override;
        DWORD getProcessId();
};

#endif // PROCESS_CONTEXT_H