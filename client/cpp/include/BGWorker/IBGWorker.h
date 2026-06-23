#ifndef IBGWORKER_H
#define IBGWORKER_H
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include "../State/InterProcessCom/Pipe/Pipe.h"
#include "../State/InterProcessCom/PipeBuilder/PipeBuilder.h"
#include "./Context/BGWorkerContext.h"
#include "./Context/BGWorkerContextSingleton.h"

class IBGWorker
{
    protected:
        bool joinable;
        virtual void act() = 0;
        virtual void run();
        virtual void pause();
        std::unique_ptr<std::thread> thread;
        std::unique_ptr<std::vector<Pipe>> pipes;
    public:
        IBGWorker();
        IBGWorker(bool joinable);
        IBGWorker(bool running, bool paused);
        ~IBGWorker() = default;
        virtual void start(bool detached = false); 
        virtual void stop();
        virtual void join();
};

#endif // IBGWORKER_H