#include "Object.h"

Object::Object()
:   data(nullptr),
    id(NULL)
{}

Object::Object(const std::vector<std::byte>& _data)
:    id(NULL)
{
    if (_data.size() < 2)
    {
        std::cout << "Data size is too small to contain an id." << "\n";
    }
    else 
    {
        std::cout << "Data size is sufficient to contain an id." << "\n";
    }

    this->data = std::make_shared<std::vector<std::byte>>(
        std::vector<std::byte>(_data.begin(), _data.end())
    );

    std::cout << "Obj construction  " << "\n";
    if (this->data != nullptr && this->data->size() >= 2)
    {
        this->id = (
            static_cast<uint16_t>(this->data->at(0)) | 
            (static_cast<uint16_t>(this->data->at(1)) << 8)
        );
        std::cout << "Id created: " << this->id << "\n";
    }
    std::cout << "Data moved: " << this->id << "\n";
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
