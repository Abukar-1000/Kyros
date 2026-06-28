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
            // std::cout << "Request queued with id: " << _request.getId() << std::endl;
            break;
        }
    }

    if (!queued)
    {
        this->requests.push_back(std::move(request));
        // std::cout << "Request added with id: " << request.getId() << std::endl;
    }

    // std::cout << "\n\n\n\n\nRequest queued SIZE " << this->requests.size() << "\n\n\n\n\n" << std::endl;
}

void BGWorkerParams::queueRequest(DurativeRequest request)
{
    std::lock_guard<std::mutex> lock(lockInstance);
    bool queued = false;
    for(auto& _request: this->durativeRequests)
    {
        if (_request == request)
        {
            queued = true;
            break;
        }
    }

    if (!queued)
    {
        this->durativeRequests.push_back(request);
    }
}

void BGWorkerParams::flushRequests(void)
{
    this->requests.erase(
        std::remove_if(
            this->requests.begin(),
            this->requests.end(),
            [](Object request)
            {
                return request.isExecuted();
            }
        )
    );
}

void BGWorkerParams::flushDurativeRequests(void)
{
    this->durativeRequests.erase(
        std::remove_if(
            this->durativeRequests.begin(),
            this->durativeRequests.end(),
            [](DurativeRequest request)
            {
                return request.isExpired();
            }
        )
    );
}