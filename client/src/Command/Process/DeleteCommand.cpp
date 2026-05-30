#include "../../../include/Command/Process/DeleteCommand.h"

DeleteCommand::DeleteCommand() 
:   targetProcessName("")
{}

DeleteCommand::DeleteCommand(const std::string& targetProcessName)
:   targetProcessName(targetProcessName)
{}

void DeleteCommand::accept(IProcessVisitor& visitor)
{
    visitor.visit(*this);
}

void DeleteCommand::execute()
{
    auto context = CommandContextSingleton::get();
    context->processItterator->reset();

    /* Lock */
    for (size_t i = 0; i < context->processList->size(); i++)
    {
        if (context->processList->at(i).getProcessName() == targetProcessName)
        {
            if (context->processList->at(i).isRunning())
            {
                std::cout << "Killing process: " << context->processList->at(i).toString() << std::endl;
                context->processList->at(i).kill();
            }

            break;
        }
    }
}