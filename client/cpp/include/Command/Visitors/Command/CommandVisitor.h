#ifndef COMMAND_VISITOR_H
#define COMMAND_VISITOR_H
#include "../../Process/DeleteCommand.h"
#include "../../../../models/Process/KillFrame.h"
#include "../../../../models/Process/KillFrameWithDuration.h"
namespace Command::Visitors
{
    namespace IPC = ::Models::Process::InterProcessCom;
    class CommandVisitor
    {
        public:
            CommandVisitor() = default;
            void operator()(const std::monostate&) const;
            void operator()(const IPC::KillFrame& frame);
            void operator()(const IPC::KillFrameWithDuration& frame);
    };
}

#endif // COMMAND_VISITOR_H