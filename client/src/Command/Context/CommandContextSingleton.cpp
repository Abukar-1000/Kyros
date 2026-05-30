#include "../../../include/Command/Context/CommandContextSingleton.h"

std::shared_ptr<CommandContext> CommandContextSingleton::instance = nullptr;

std::shared_ptr<CommandContext> CommandContextSingleton::get()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<CommandContext>();
    }

    return instance;
}