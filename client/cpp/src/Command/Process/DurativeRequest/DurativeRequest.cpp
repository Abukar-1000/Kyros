#include "../../../../include/Command/Process/DurativeRequest/DurativeRequest.h"

std::atomic<uint32_t> DurativeRequest::atomicCounter(0);

uint32_t DurativeRequest::getNextUniqueId()
{
    return DurativeRequest::atomicCounter.fetch_add(1);
}

DurativeRequest::DurativeRequest(int64_t expiresIn, Object request)
:   id(DurativeRequest::getNextUniqueId()),
    request(request)
{
    auto milliseconds = this->getEllapsedMilliseconds();
    this->expirationTime = milliseconds + expiresIn;
}

int64_t DurativeRequest::getEllapsedMilliseconds() const
{
    auto init = std::chrono::steady_clock::now();
    auto ellapsed = init.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(ellapsed).count();
}

int64_t DurativeRequest::getExpirationTime() const
{
    return this->expirationTime;
}

void DurativeRequest::setExpirationTime(int64_t expirationTime)
{
    this->expirationTime = expirationTime;
}

bool DurativeRequest::isQueued() const
{
    return this->queued;
}

void DurativeRequest::setIsQueued(bool queued)
{
    this->queued = queued;
}

bool DurativeRequest::isExpired() const
{
    return this->getEllapsedMilliseconds() >= this->getExpirationTime();
}

bool DurativeRequest::operator==(const DurativeRequest& other) const
{
    return this->id == other.id;
}