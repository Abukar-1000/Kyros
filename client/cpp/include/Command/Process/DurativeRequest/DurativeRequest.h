#ifndef DURATIVE_REQUEST_H
#define DURATIVE_REQUEST_H
#include "../../../../models/Object/Object.h"
#include <iostream>
#include <chrono>
#include <cstdint>
#include <atomic>

class DurativeRequest
{
    private:
        uint32_t id;
        int64_t expirationTime;
        Object request;
        bool queued;
        static std::atomic<uint32_t> atomicCounter;
        static uint32_t getNextUniqueId();
        int64_t getEllapsedMilliseconds() const;
    public:
        virtual ~DurativeRequest() = default;
        DurativeRequest(int64_t expirationTime, Object request);
        int64_t getExpirationTime() const;
        void setExpirationTime(int64_t expirationTime);
        bool isQueued() const;
        void setIsQueued(bool queued);
        bool isExpired() const;
        bool operator==(const DurativeRequest& other) const;
        Object& getRequest(void);
};

inline Object& DurativeRequest::getRequest(void)
{
    return this->request;
}

#endif // DURATIVE_REQUEST_H
