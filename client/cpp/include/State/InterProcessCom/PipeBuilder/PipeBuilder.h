#ifndef PIPE_BUILDER_H
#define PIPE_BUILDER_H
#include <windows.h>
#include <string>
#include "../Pipe/Pipe.h"

class PipeBuilder
{
    private:
        std::wstring name;
        DWORD openMode;
        DWORD pipeMode;
        size_t maxInstances;
        size_t inBufferSize;
        size_t outBufferSize;
        size_t defaultTimeout;
        LPSECURITY_ATTRIBUTES securityAttributes;
    public:
        PipeBuilder(void);
        ~PipeBuilder(void) = default;
        PipeBuilder& withName(std::wstring name);
        PipeBuilder& withOpenMode(DWORD openMode);
        PipeBuilder& withPipeMode(DWORD pipeMode);
        PipeBuilder& withMaxInstances(size_t maxInstances);
        PipeBuilder& withInBufferSize(size_t inBufferSize);
        PipeBuilder& withOutBufferSize(size_t outBufferSize);
        PipeBuilder& withDefaultTimeout(size_t defaultTimeout);
        PipeBuilder& withSecurityAttributes(LPSECURITY_ATTRIBUTES securityAttributes);
        Pipe build(void);
};

#endif // PIPE_BUILDER_H