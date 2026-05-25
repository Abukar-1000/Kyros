#ifndef BINARY_BUILDER_H
#define BINARY_BUILDER_H
#include <vector>
#include <memory>
#include <cstddef>
/**
 * @brief This class converts a struct or class into raw binary data.
 * It returns a vector if bytes representing the fields in the exact
 * order they where provided.
 * 
 */

class BinaryBuilder
{
    private:
        std::shared_ptr<std::vector<std::byte>> binaryData;
    public:
        BinaryBuilder();
        ~BinaryBuilder() = default;
        BinaryBuilder(size_t initialSize);

        template<typename T>
        BinaryBuilder& with(T value)
        {
            const std::byte* bytePtr = reinterpret_cast<const std::byte*>(&value);
            binaryData->insert(binaryData->end(), bytePtr, bytePtr + sizeof(T));
            return *this;
        }

        std::shared_ptr<std::vector<std::byte>> build(void);
};

#endif // BINARY_BUILDER_H