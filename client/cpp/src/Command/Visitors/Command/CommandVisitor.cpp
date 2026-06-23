#include "../../../../include/Command/Visitors/Command/CommandVisitor.h"


namespace Command::Visitors
{
    namespace IPC = ::Models::Process::InterProcessCom;
    void CommandVisitor::operator()(const IPC::KillFrame& frame)
    {
        std::cout << "Received KillFrame with id: " << frame.id 
                  << ", processId: " << frame.processId 
                  << ", processName: " << frame.processName << std::endl;
        auto command = DeleteCommand(frame.processName);
        command.execute();
    }

    void CommandVisitor::operator()(const std::monostate&) const
    {
        std::cout << "Visitor ignored an empty or invalid frame." << std::endl;
    }
}