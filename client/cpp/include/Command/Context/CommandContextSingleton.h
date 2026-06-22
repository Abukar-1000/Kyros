#ifndef COMMAND_CONTEXT_SINGLETON_H
#define COMMAND_CONTEXT_SINGLETON_H
#include "CommandContext.h"

class CommandContextSingleton
{
    private:
        static std::shared_ptr<CommandContext> instance;
    public:
        CommandContextSingleton() = default;
        ~CommandContextSingleton() = default;
        static std::shared_ptr<CommandContext> get();
};

#endif // COMMAND_CONTEXT_SINGLETON_H