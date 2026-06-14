#ifndef BGWORKER_CONTEXT_SINGLETON_H
#define BGWORKER_CONTEXT_SINGLETON_H
#include <memory>
#include <mutex>
#include "BGWorkerContext.h"


class BGWorkerContextSingleton
{
    private:
        static std::shared_ptr<BGWorkerContext> instance;
        static std::mutex lockInstance;
    public:
        BGWorkerContextSingleton() = default;
        ~BGWorkerContextSingleton() = default;
        static std::shared_ptr<BGWorkerContext> get();
};

#endif // BGWORKER_CONTEXT_SINGLETON_H