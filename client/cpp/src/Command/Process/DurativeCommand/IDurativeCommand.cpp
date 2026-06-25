#include "../../../../include/Command/Process/DurativeCommand/IDurativeCommand.h"

std::atomic<uint32_t> IDurativeCommand::atomicCounter(0);

uint32_t IDurativeCommand::getNextUniqueId()
{
    return IDurativeCommand::atomicCounter.fetch_add(1);
}

IDurativeCommand::IDurativeCommand(int64_t expiresIn)
:   id(IDurativeCommand::getNextUniqueId())
{
    auto milliseconds = this->getEllapsedMilliseconds();
    this->expirationTime = milliseconds + expiresIn;
}

int64_t IDurativeCommand::getEllapsedMilliseconds() const
{
    auto init = std::chrono::steady_clock::now();
    auto ellapsed = init.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(ellapsed).count();
}

int64_t IDurativeCommand::getExpirationTime() const
{
    return this->expirationTime;
}

void IDurativeCommand::setExpirationTime(int64_t expirationTime)
{
    this->expirationTime = expirationTime;
}

bool IDurativeCommand::isQueued() const
{
    return this->queued;
}

void IDurativeCommand::setIsQueued(bool queued)
{
    this->queued = queued;
}

bool IDurativeCommand::isExpired() const
{
    return this->getEllapsedMilliseconds() >= this->getExpirationTime();
}

bool IDurativeCommand::operator==(const IDurativeCommand& other) const
{
    return this->id == other.id;
}