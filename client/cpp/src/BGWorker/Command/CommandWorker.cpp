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
    this->commandVisitor = Visitors::CommandVisitor();
}

void CommandWorker::act()
{
    auto context = BGWorkerContextSingleton::get();
    // auto requests = context->commandParams->getRequests();
    // std::cout << "Processing requests, count: " << requests.size() << std::endl;
    for(auto& req: context->commandParams->getRequests())
    {
        if (!req.isExecuted())
        {
            std::cout << "Request received with id: " << req.getId() << std::endl;
            auto frame = this->GetFrame(req);
            std::cout << "Handing off to visitor" << std::endl;
            std::visit(this->commandVisitor, frame);
            req.setExecuted(true);
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

Frame CommandWorker::GetFrame(Object request)
{
    //
    if (request.getId() == static_cast<uint16_t>(Frames::Tag::COMMAND_KILL_PROCESS))
    {
        auto data = request.getData();
        std::cout << "Creating KillFrame from request with id: " << request.getId() << std::endl;
        if (data == nullptr)
        {
            std::cout << "Request data is null for request with id: " << request.getId() << std::endl;
            return std::monostate{};
        }
        else
        {
            std::cout << "Request data size: " 
            << data->size() << " for request with id: " << request.getId() 
            << " should be of size " << sizeof(Frames::KillFrame) << std::endl;
        }

        if (data != nullptr && data->size() >= sizeof(Frames::KillFrame))
        {
            std::cout << "Data size is sufficient for KillFrame, creating frame..." << std::endl;
            Frames::KillFrame frame;
            std::memcpy(&frame, data->data(), sizeof(Frames::KillFrame));
            std::cout << "Frame created with id: " << frame.id 
                      << ", processId: " << frame.processId 
                      << ", processName: " << frame.processName << std::endl;
            return frame;
        }
    }

    return std::monostate{}; 
}