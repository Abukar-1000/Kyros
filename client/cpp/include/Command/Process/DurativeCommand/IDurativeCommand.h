#ifndef IDURATIVE_COMMAND_H
#define IDURATIVE_COMMAND_H
#include "../../ICommand.h"
#include <iostream>
#include <chrono>
#include <cstdint>
#include <atomic>

class IDurativeCommand: public ICommand
{
    private:
        uint32_t id;
        int64_t expirationTime;
        bool queued;
        static std::atomic<uint32_t> atomicCounter;
        static uint32_t getNextUniqueId();
        int64_t getEllapsedMilliseconds() const;
    public:
        virtual ~IDurativeCommand() = default;
        IDurativeCommand(int64_t expirationTime);
        int64_t getExpirationTime() const;
        void setExpirationTime(int64_t expirationTime);
        bool isQueued() const;
        void setIsQueued(bool queued);
        bool isExpired() const;
        bool operator==(const IDurativeCommand& other) const; 
};
#endif // IDURATIVE_COMMAND_H
