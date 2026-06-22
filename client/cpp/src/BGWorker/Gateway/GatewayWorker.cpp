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
    auto context = BGWorkerContextSingleton::get();
    // const bool isSmallBuffer = (
    //     context != nullptr && 
    //     context->commandParams != nullptr && 
    //     context->commandParams->getRequests().size() < 1024
    // );
    
    // std::cout << "resize " << isSmallBuffer << std::endl;
    // if (isSmallBuffer)
    // {
    //     context->commandParams->getRequests().reserve(1024);
    // }
    // std::cout << "running  " << isSmallBuffer << std::endl;

    if (this->connected)
    {
        // std::cout << "connected  " << std::endl;
        if (this->pipe.hasData())
        {
            auto bytes = this->pipe.receiveBytes<std::vector<std::byte>>();
            // std::cout << "Byte array Created  " << "\n";
            
            // std::cout << "Enumerating:  " << "\n";
            // for (size_t i = 0; i < bytes.size(); i++)
            // {
            //     std::cout << "Index: " << i << " Hex: " << static_cast<int>(bytes[i]) << "\n";
            //     std::cout << static_cast<int>(bytes[i]) << " ";
            // }
            // std::cout << std::endl;

            auto payload = Object(std::move(bytes));
            std::cout << "Obj Created  " << "\n";
            std::cout << "Received request with id: " 
                        << payload.getId() << " size: " 
                        << payload.getData()->size() * sizeof(std::byte) 
                        << std::endl;
            context->commandParams->addRequest(payload);
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}