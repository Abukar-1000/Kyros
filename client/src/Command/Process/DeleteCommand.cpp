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
    std::cout << "killing\n" << std::endl;
    
    context->markAndSweep();
    /* Lock */
    for (size_t i = 0; i < context->processList->size(); i++)
    {
        if (context->processList->at(i).getProcessName() == targetProcessName)
        {
            context->processList->at(i).kill();
            // break;
        }
    }
}