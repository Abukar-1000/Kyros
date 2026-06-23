#include "../../../include/BGWorker/Context/BGWorkerParams.h"

void BGWorkerParams::setRunning(bool running)
{
    std::lock_guard<std::mutex> lock(lockInstance);    
    this->running = running;
}

void BGWorkerParams::setPaused(bool paused)
{
    std::lock_guard<std::mutex> lock(lockInstance);    
    this->paused = paused;
}

void BGWorkerParams::addRequest(Object request)
{
    std::lock_guard<std::mutex> lock(lockInstance);
    bool queued = false;
    for (auto& _request : this->requests)
    {
        if (_request.isExecuted())
        {
            _request = std::move(request);
            queued = true;
            std::cout << "Request queued with id: " << _request.getId() << std::endl;
            break;
        }
    }

    if (!queued)
    {
        this->requests.push_back(std::move(request));
        std::cout << "Request added with id: " << request.getId() << std::endl;
    }
}