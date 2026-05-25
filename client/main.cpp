#include <iostream>
#include <vector>
#include "./include/Process/Context/ProcessContext.h"
#include "./include/Process/Observer/ProcessObserver.h"
#include "./include/Process/Itterator/ProcessItterator.h"
#include "./include/State/InterProcessCom/Pipe/Pipe.h"
#include "./include/State/InterProcessCom/PipeBuilder/PipeBuilder.h"
#include "./include/State/BinaryBuilder/BinaryBuilder.h"
#include "./include/Process/Process.h"
#include <cstddef>

struct ProcessInfo
{
    uint32_t processId;
    char processName[256];
};

int main() {
    std::cout << "Hello, World! Kyros" << std::endl;
    auto pipeBuilder = PipeBuilder();
    Pipe pipe = pipeBuilder
        .withName(L"\\\\.\\pipe\\ProcessPipe")
        .withOpenMode(PIPE_ACCESS_DUPLEX)
        .withPipeMode(PIPE_TYPE_BYTE | PIPE_WAIT)
        .withMaxInstances(2)
        .withInBufferSize(1024)
        .withOutBufferSize(1024)
        .withDefaultTimeout(0)
        .withSecurityAttributes(nullptr)
        .build();

    std::cout << "Server connecting..." << std::endl;
    pipe.connect();
    std::cout << "Server running..." << std::endl;

    std::cout << "\n\nBuilding complex structure..." << std::endl;
    auto mockData = ProcessInfo{1234, "MockProcess.exe"};
    auto binaryBuilder = BinaryBuilder();
    auto binaryData = binaryBuilder.with(mockData).build();
    
    std::cout << "Sending complex structure..." << std::endl;
    pipe.send<std::vector<std::byte>>(*binaryData);
    std::cout << "Sent complex structure..." << std::endl;

    std::cout << "Receiving complex structure..." << std::endl;
    auto mockReceive = pipe.receiveBytes<ProcessInfo>();

    std::cout << "Received complex structure..." << std::endl;
    std::cout << "Process ID: " << mockReceive.processId << std::endl;
    std::cout << "Process Name: " << mockReceive.processName << std::endl;
    
    Sleep(10 * 1000);
    pipe.close();
    return 0;
}