#include "../../../include/BGWorker/Context/BGWorkerContextSingleton.h"

std::shared_ptr<BGWorkerContext> BGWorkerContextSingleton::instance = nullptr;
std::mutex BGWorkerContextSingleton::lockInstance;

std::shared_ptr<BGWorkerContext> BGWorkerContextSingleton::get()
{
    std::lock_guard<std::mutex> lock(lockInstance);    
    if (instance == nullptr)
    {
        instance = std::make_shared<BGWorkerContext>();
    }
    
    return instance;
}
