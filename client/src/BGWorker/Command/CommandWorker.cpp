#include "../../../include/BGWorker/Command/CommandWorker.h"

CommandWorker::CommandWorker() 
:   IBGWorker() 
{}

void CommandWorker::act()
{
    auto context = BGWorkerContextSingleton::get();
    std::string name = "Discord";
    auto deleteCommand = DeleteCommand(name);
    auto processVisitor = std::make_shared<ProcessVisitor>();
    deleteCommand.accept(*processVisitor);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}