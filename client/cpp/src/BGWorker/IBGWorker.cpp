#include "../../include/BGWorker/IBGWorker.h"

IBGWorker::IBGWorker()
:   thread(nullptr),
    pipes(std::make_unique<std::vector<Pipe>>())
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->setRunning(false);
    context->commandParams->setPaused(false);
}

IBGWorker::IBGWorker(bool joinable)
:   joinable(joinable), 
    thread(nullptr),
    pipes(std::make_unique<std::vector<Pipe>>())
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->setRunning(false);
    context->commandParams->setPaused(false);
}

IBGWorker::IBGWorker(bool running, bool paused)
:   thread(nullptr),
    pipes(std::make_unique<std::vector<Pipe>>())
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->setRunning(running);
    context->commandParams->setPaused(paused);
}

void IBGWorker::run()
{
    auto context = BGWorkerContextSingleton::get();
    while (context->commandParams->getRunning())
    {
        if (context->commandParams->getPaused())
        {
            std::cout << "<<Skipping execution>>" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        // std::cout << "[ACT]" << std::endl;
        this->act();
    }
}

void IBGWorker::start(bool detached)
{
    auto context = BGWorkerContextSingleton::get();
    // if (context->commandParams->getRunning())
    // {
    //     return;
    // }

    std::cout << "Starting..." << std::endl;
    context->commandParams->setRunning(true);
    thread = std::make_unique<std::thread>(&IBGWorker::run, this);
    thread->detach();
    std::cout << "Detached " << std::endl;
}

void IBGWorker::stop()
{
    auto context = BGWorkerContextSingleton::get();
    if (!context->commandParams->getRunning())
    {
        return;
    }

    std::cout << "Stopping..." << std::endl;
    
    const bool safeToJoin = (
        thread != nullptr && 
        this->thread->get_id() != std::this_thread::get_id() && 
        joinable && thread->joinable()
    );
    
    if (safeToJoin)
    {
        thread->detach();
        context->commandParams->setRunning(false);
    }

    std::cout << "Stopping DONE..." << std::endl;
}

void IBGWorker::pause()
{
    auto context = BGWorkerContextSingleton::get();
    context->commandParams->setPaused(true);
    std::cout << "Paused" << std::endl;
}

void IBGWorker::join()
{
    joinable = true;
}
