#ifndef Object_H
#define Object_H
#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include "../Tags.h"

using SharedBytes = std::shared_ptr<std::vector<std::byte>>;
class Object
{
    private:
        uint16_t id;
        SharedBytes data;
        bool executed;
    public:
        ~Object() = default;
        Object();
        Object& operator=(const Object& other);
        Object(const std::vector<std::byte>& data);
        void withData(std::vector<std::byte> data);
        const SharedBytes getData();
        const uint16_t getId();
        bool isExecuted() const;
        void setExecuted(bool executed);
        std::vector<std::byte> release();
};

inline bool Object::isExecuted() const
{
    return this->executed;
}

inline void Object::setExecuted(bool executed)
{
    this->executed = executed;
}
#endif // Object_H