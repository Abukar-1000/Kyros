#include "../../../include/BGWorker/Gateway/GatewayWorker.h"

GatewayWorker::GatewayWorker()
:   IBGWorker(),
    connected(false)
{
    this->pipe = PipeBuilder()
            .withName(L"\\\\.\\pipe\\GatewayPipe")
            .withOpenMode(PIPE_ACCESS_DUPLEX)
            .withPipeMode(PIPE_TYPE_BYTE | PIPE_WAIT)
            .withMaxInstances(2)
            .withInBufferSize(1024)
            .withOutBufferSize(1024)
            .withDefaultTimeout(0)
            .withSecurityAttributes(nullptr)
            .build();
    this->connected = this->pipe.connect();
}

void GatewayWorker::act()
{
    // std::cout << "GatewayWorker::act() called" << std::endl;
    auto context = BGWorkerContextSingleton::get();
    if (this->connected)
    {
        if (this->pipe.hasData())
        {
            auto bytes = this->pipe.receiveBytes<std::vector<std::byte>>();
            auto payload = Object(std::move(bytes));
            std::cout << "Obj Created  " << "\n";
            std::cout << "Received request with id: " 
                        << payload.getId() << " size: " 
                        << payload.getData()->size() * sizeof(std::byte) 
                        << std::endl;
            this->queueRequest(payload);
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void GatewayWorker::queueRequest(Object& request)
{
    auto context = BGWorkerContextSingleton::get();
    if (request.getId() & Frames::DURATIVE_COMMAND > 0)
    {
        context->commandParams->queueRequest(
            DurativeRequest(60 * 1000, std::move(request))
        );
        return;
    }
    context->commandParams->addRequest(std::move(request));
}