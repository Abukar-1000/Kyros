#include <iostream>
#include <vector>
#include "./include/Process/Context/ProcessContext.h"
#include "./include/Process/Observer/ProcessObserver.h"
#include "./include/Process/Itterator/ProcessItterator.h"
#include "./include/State/InterProcessCom/Pipe/Pipe.h"
#include "./include/State/InterProcessCom/PipeBuilder/PipeBuilder.h"
#include "./include/Process/Process.h"

int main() {
    std::cout << "Hello, World! Kyros" << std::endl;
    auto pipeBuilder = PipeBuilder();
    Pipe pipe = pipeBuilder
        .withName(L"\\\\.\\pipe\\ProcessPipe")
        .withOpenMode(PIPE_ACCESS_DUPLEX)
        .withPipeMode(PIPE_TYPE_BYTE | PIPE_WAIT)
        .withMaxInstances(1)
        .withInBufferSize(1024)
        .withOutBufferSize(1024)
        .withDefaultTimeout(0)
        .withSecurityAttributes(nullptr)
        .build();

    std::cout << "Server connecting..." << std::endl;
    pipe.connect();
    std::cout << "Server running..." << std::endl;
    return 0;
}