#ifndef BGWORKER_PARAMS_H
#define BGWORKER_PARAMS_H
#include <mutex>
#include <memory>

class BGWorkerParams
{
    private:
        bool running;
        bool paused;
        std::mutex lockInstance;
    public:
        BGWorkerParams() = default;
        ~BGWorkerParams() = default;
        bool getRunning();
        bool getPaused();
        void setRunning(bool running);
        void setPaused(bool paused);
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

#endif // BGWORKER_PARAMS_H