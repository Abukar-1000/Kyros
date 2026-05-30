#ifndef ICOMMAND_H
#define ICommand_H
#include "./Context/CommandContextSingleton.h"

class ICommand
{
    protected:
        std::shared_ptr<CommandContext> context;
    public:
        virtual ~ICommand() = default;
        virtual void execute() = 0;
};

#endif // ICOMMAND_H