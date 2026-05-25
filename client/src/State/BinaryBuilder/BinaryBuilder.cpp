#include "../../include/State/BinaryBuilder/BinaryBuilder.h"

BinaryBuilder::BinaryBuilder(void)
:   binaryData(std::make_shared<std::vector<std::byte>>())
{}

BinaryBuilder::BinaryBuilder(size_t initialSize) 
:   binaryData(std::make_shared<std::vector<std::byte>>())

{
    binaryData->reserve(initialSize);
}


std::shared_ptr<std::vector<std::byte>> BinaryBuilder::build(void)
{
    return binaryData;
}