#ifndef BGWORKER_PARAMS_H
#define BGWORKER_PARAMS_H
#include <mutex>
#include <memory>
#include <vector>
#include "../../../models/Object/Object.h"
#include "../../Command/Process/DurativeCommand/IDurativeCommand.h"

class BGWorkerParams
{
    private:
        bool running;
        bool paused;
        std::mutex lockInstance;
        std::vector<Object> requests;
        std::vector<IDurativeCommand> durativeRequests;
    public:
        BGWorkerParams() = default;
        ~BGWorkerParams() = default;
        bool getRunning();
        bool getPaused();
        void setRunning(bool running);
        void setPaused(bool paused);
        void addRequest(Object request);
        void queueRequest(IDurativeCommand request);
        std::vector<IDurativeCommand> getQueuedRequests();
        std::vector<Object> getRequests();
};

inline bool BGWorkerParams::getRunning()
{
    std::lock_guard<std::mutex> lock(lockInstance);
    return this->running;
}

inline bool BGWorkerParams::getPaused()
{
    std::lock_guard<std::mutex> lock(lockInstance);
    return this->paused;
}

inline std::vector<Object> BGWorkerParams::getRequests()
{
    std::lock_guard<std::mutex> lock(lockInstance);
    return this->requests;
}

inline std::vector<IDurativeCommand> BGWorkerParams::getQueuedRequests()
{
    std::lock_guard<std::mutex> lock(lockInstance);
    return this->durativeRequests;
}
#endif // BGWORKER_PARAMS_H