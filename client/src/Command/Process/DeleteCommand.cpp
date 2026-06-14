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
    
    context->markAndSweep();
    for (auto it = context->processMap->begin(); it != context->processMap->end(); it++)
    {
        if (it->second.getProcessName() == targetProcessName)
        {
            it->second.kill();
        }
    }
}