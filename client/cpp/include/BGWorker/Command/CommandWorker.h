#ifndef COMMAND_WORKER_H
#define COMMAND_WORKER_H
#include <string>
#include <variant>
#include "../IBGWorker.h"
#include "../../../models/Tags.h"
#include "../../../models/Object/Object.h"
#include "../../../models/Process/KillFrame.h"
#include "../../Command/Process/DeleteCommand.h"
#include "../../Command/Visitors/ProcessVisitor.h"
#include "../../Command/Visitors/Command/CommandVisitor.h"

namespace Visitors = Command::Visitors;
namespace Frames = Models::Process::InterProcessCom;

using Frame = std::variant<
    std::monostate,
    Frames::KillFrame
>;

class CommandWorker : public IBGWorker
{
    private:
        Visitors::CommandVisitor commandVisitor;
        Frame GetFrame(Object request);
        void act() override;
    public:
        CommandWorker();
};
#endif // COMMAND_WORKER_H