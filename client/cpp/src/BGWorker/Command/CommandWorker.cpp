#include "../../../include/BGWorker/Command/CommandWorker.h"

CommandWorker::CommandWorker() 
:   IBGWorker() 
{
    this->pipes->push_back(
        PipeBuilder()
            .withName(L"\\\\.\\pipe\\CommandPipe")
            .withOpenMode(PIPE_ACCESS_DUPLEX)
            .withPipeMode(PIPE_TYPE_BYTE | PIPE_WAIT)
            .withMaxInstances(2)
            .withInBufferSize(1024)
            .withOutBufferSize(1024)
            .withDefaultTimeout(0)
            .withSecurityAttributes(nullptr)
            .build()
    );
}

void CommandWorker::act()
{
    auto context = BGWorkerContextSingleton::get();
    std::string name = "Discord";
    auto deleteCommand = DeleteCommand(name);
    auto processVisitor = std::make_shared<ProcessVisitor>();
    deleteCommand.accept(*processVisitor);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}