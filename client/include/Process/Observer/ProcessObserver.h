#ifndef PROCESS_OBSERVER_H
#define PROCESS_OBSERVER_H
#include <iostream>
#include <vector>
#include "../../State/Observer/IObserver.h"
#include "../Process.h"

using SharedProcessList = std::shared_ptr<std::vector<Process>>;
class ProcessObserver : public IObserver<SharedProcessList>
{
    public:
        ProcessObserver();
        void update(SharedProcessList value) override;
};

#endif // PROCESS_OBSERVER_H