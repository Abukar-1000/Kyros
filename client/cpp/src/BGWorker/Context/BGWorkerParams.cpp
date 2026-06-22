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