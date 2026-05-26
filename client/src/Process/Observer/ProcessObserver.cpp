#include "../../include/Process/Observer/ProcessObserver.h"

ProcessObserver::ProcessObserver() 
{
    this->pipe = std::make_unique<Pipe>(
        PipeBuilder()
            .withName(L"\\\\.\\pipe\\ProcessPipe")
            .withOpenMode(PIPE_ACCESS_OUTBOUND)
            .withPipeMode(PIPE_TYPE_BYTE | PIPE_WAIT)
            .withMaxInstances(1)
            .withInBufferSize(1024)
            .withOutBufferSize(1024)
            .withDefaultTimeout(0)
            .withSecurityAttributes(nullptr)
            .build()
    );
    this->binaryBuilder = std::make_unique<BinaryBuilder>();
}

void ProcessObserver::update(SharedProcessList value)
{
    this->pipe->connect();
    std::cout << "Received update with " << value->size() << " processes." << std::endl;
    
    auto metadata = Models::Process::InterProcessCom::ProcessFrame 
    {
        0,
        ""
    }; 
    
    size_t count = 0;
    for (size_t i = 0; i < value->size(); i++)
    {
        this->binaryBuilder->reset();
        auto process = value->at(i);
        
        if (process.getProcessName() == "[UNKNOWN]")
        {
            continue;
        }

        metadata.withValues(process.getProcessId(), process.getProcessName().c_str());
        auto binaryData = this->binaryBuilder->with(metadata).build();
        this->pipe->send<std::vector<std::byte>>(*binaryData);
        count++;
    }

    std::cout << "Sent " << count << " processes." << std::endl;
    this->pipe->close();
} 