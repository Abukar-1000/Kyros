#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H
#include <vector>
#include <memory>
#include <windows.h>
#include "../ICommand.h"
#include "../../Process/Process.h"
#include "../Visitors/IProcessVisitor.h"
#include "../Visitees/IProcessVisitee.h"
#include "../../Process/Itterator/ProcessItterator.h"

class DeleteCommand : public ICommand, public IProcessVisitee
{
    private:
        std::string targetProcessName;
    public:
        DeleteCommand();
        DeleteCommand(const std::string& targetProcessName);
        ~DeleteCommand() override = default;
        void execute() override;
        void accept(IProcessVisitor& visitor) override;
};

#endif // DELETE_COMMAND_H