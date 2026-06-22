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
    public:
        ~Object() = default;
        Object();
        Object(const std::vector<std::byte>& data);
        void withData(std::vector<std::byte> data);
        const SharedBytes getData();
        const uint16_t getId();
        std::vector<std::byte> release();
};

#endif // Object_H