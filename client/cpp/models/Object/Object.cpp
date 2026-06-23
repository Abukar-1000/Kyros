#include "Object.h"

Object::Object()
:   data(nullptr),
    id(NULL),
    executed(false)
{}

Object::Object(const std::vector<std::byte>& _data)
:   id(NULL),
    executed(false)
{
    this->data = std::make_shared<std::vector<std::byte>>(
        std::vector<std::byte>(_data.begin(), _data.end())
    );

    // std::cout << "Obj construction  " << "\n";
    if (this->data != nullptr && this->data->size() >= 2)
    {
        this->id = (
            static_cast<uint16_t>(this->data->at(0)) | 
            (static_cast<uint16_t>(this->data->at(1)) << 8)
        );
        std::cout << "Id created: " << this->id << "\n";
    }
    // std::cout << "Data moved: " << this->id << "\n";
}

void Object::withData(std::vector<std::byte> data)
{
    this->data = std::make_shared<std::vector<std::byte>>(std::move(data));
}

const SharedBytes Object::getData()
{
    return this->data;
}

std::vector<std::byte> Object::release()
{
    std::vector<std::byte> temp = *data;
    this->data = nullptr;
    return temp;
}

const uint16_t Object::getId()
{
    return this->id;
}

Object& Object::operator=(const Object& other)
{
    if (this != &other)
    {
        this->id = other.id;
        this->data = other.data;
        this->executed = other.executed;
    }
    return *this;
}
