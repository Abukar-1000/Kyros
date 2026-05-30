#ifndef COMMAND_WORKER_H
#define COMMAND_WORKER_H
#include <string>
#include "../IBGWorker.h"
#include "../../Command/Process/DeleteCommand.h"
#include "../../Command/Visitors/ProcessVisitor.h"


class CommandWorker : public IBGWorker
{
    private:
        void act() override;
    public:
        CommandWorker();
};
#endif // COMMAND_WORKER_H