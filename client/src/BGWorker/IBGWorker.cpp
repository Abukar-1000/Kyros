#include "../../include/BGWorker/IBGWorker.h"

IBGWorker::IBGWorker()
:   thread(nullptr)
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->running = false;
    context->commandParams->paused = false;
}

IBGWorker::IBGWorker(bool joinable)
:   joinable(joinable), 
    thread(nullptr)
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->running = false;
    context->commandParams->paused = false;
}

IBGWorker::IBGWorker(bool running, bool paused)
:   thread(nullptr)
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->running = running;
    context->commandParams->paused = paused;
}

void IBGWorker::run()
{
    auto context = BGWorkerContextSingleton::get();
    while (context->commandParams->running)
    {
        if (context->commandParams->paused)
        {
            std::cout << "<<Skipping execution>>" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        // std::cout << "[ACT]" << std::endl;
        this->act();
    }
}

void IBGWorker::start()
{
    auto context = BGWorkerContextSingleton::get();
    if (context->commandParams->running)
    {
        return;
    }

    std::cout << "Starting..." << std::endl;
    context->commandParams->running = true;
    thread = std::make_unique<std::thread>(&IBGWorker::run, this);
}

void IBGWorker::stop()
{
    auto context = BGWorkerContextSingleton::get();
    if (!context->commandParams->running)
    {
        return;
    }

    std::cout << "Stopping..." << std::endl;
    context->commandParams->running = false;
    
    const bool safeToJoin = (
        thread != nullptr && 
        this->thread->get_id() != std::this_thread::get_id() && 
        joinable && thread->joinable()
    );
    
    if (safeToJoin)
    {
        thread->join();
    }
    std::cout << "Stopping DONE..." << std::endl;
}

void IBGWorker::pause()
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->paused = true;
    std::cout << "Paused" << std::endl;
}

void IBGWorker::join()
{
    joinable = true;
}
