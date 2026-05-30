#include "../../../include/BGWorker/Context/BGWorkerContextSingleton.h"

std::shared_ptr<BGWorkerContext> BGWorkerContextSingleton::instance = nullptr;
std::shared_ptr<BGWorkerContext> BGWorkerContextSingleton::get()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<BGWorkerContext>();
    }

    return instance;
}
