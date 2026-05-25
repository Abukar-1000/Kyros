#include "../../include/State/BinaryBuilder/BinaryBuilder.h"

BinaryBuilder::BinaryBuilder() {}

BinaryBuilder::BinaryBuilder(size_t initialSize) 
{
    binaryData->reserve(initialSize);
}

template<typename T>
BinaryBuilder* BinaryBuilder::with(T value)
{
    const std::byte* bytePtr = reinterpret_cast<const std::byte*>(&value);
    binaryData->insert(binaryData->end(), bytePtr, bytePtr + sizeof(T));
    return this;
}

std::shared_ptr<std::vector<std::byte>> BinaryBuilder::build(void)
{
    return binaryData;
}