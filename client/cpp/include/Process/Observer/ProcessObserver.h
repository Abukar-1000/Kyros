#ifndef PROCESS_OBSERVER_H
#define PROCESS_OBSERVER_H
#include <iostream>
#include <vector>
#include <memory>
#include "../Process.h"
#include "../../State/Observer/IObserver.h"
#include "../../../models/Process/ProcessFrame.h"
#include "../../State/InterProcessCom/Pipe/Pipe.h"
#include "../../State/BinaryBuilder/BinaryBuilder.h"
#include "../../State/BinaryBuilder/BinaryBuilder.h"
#include "../../State/InterProcessCom/PipeBuilder/PipeBuilder.h"

using SharedProcessList = std::shared_ptr<std::vector<Process>>;
class ProcessObserver : public IObserver<SharedProcessList>
{
    private:
        std::unique_ptr<Pipe> pipe;
        std::unique_ptr<BinaryBuilder> binaryBuilder;
    public:
        ProcessObserver();
        ~ProcessObserver() = default;
        void update(SharedProcessList value) override;
};

#endif // PROCESS_OBSERVER_H