#ifndef IBGWORKER_H
#define IBGWORKER_H
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>
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
    public:
        IBGWorker();
        IBGWorker(bool joinable);
        IBGWorker(bool running, bool paused);
        virtual ~IBGWorker();
        virtual void start(); 
        virtual void stop();
        virtual void join();
};

#endif // IBGWORKER_H