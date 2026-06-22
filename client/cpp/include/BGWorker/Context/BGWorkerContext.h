#ifndef BGWORKER_CONTEXT_H
#define BGWORKER_CONTEXT_H
#include <memory>
#include "BGWorkerParams.h"
using SharedParams = std::shared_ptr<BGWorkerParams>;

class BGWorkerContext
{
    public:
        BGWorkerContext();
        ~BGWorkerContext() = default;
        SharedParams commandParams;
};
#endif // BGWORKER_CONTEXT_H