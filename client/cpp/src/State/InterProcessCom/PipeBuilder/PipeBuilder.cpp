#include "../../../../include/State/InterProcessCom/PipeBuilder/PipeBuilder.h"

PipeBuilder::PipeBuilder(void) {}

Pipe PipeBuilder::build(void)
{
    return Pipe(
        this->name,
        this->openMode,
        this->pipeMode,
        this->maxInstances,
        this->inBufferSize,
        this->outBufferSize,
        this->defaultTimeout,
        this->securityAttributes
    );
}

PipeBuilder& PipeBuilder::withName(std::wstring name)
{
    this->name = name;
    return *this;
}

PipeBuilder& PipeBuilder::withOpenMode(DWORD openMode)
{
    this->openMode = openMode;
    return *this;
}

PipeBuilder& PipeBuilder::withPipeMode(DWORD pipeMode)
{
    this->pipeMode = pipeMode;
    return *this;
}

PipeBuilder& PipeBuilder::withMaxInstances(size_t maxInstances)
{
    this->maxInstances = maxInstances;
    return *this;
}

PipeBuilder& PipeBuilder::withInBufferSize(size_t inBufferSize)
{
    this->inBufferSize = inBufferSize;
    return *this;
}

PipeBuilder& PipeBuilder::withOutBufferSize(size_t outBufferSize)
{
    this->outBufferSize = outBufferSize;
    return *this;
}

PipeBuilder& PipeBuilder::withDefaultTimeout(size_t defaultTimeout)
{
    this->defaultTimeout = defaultTimeout;
    return *this;
}

PipeBuilder& PipeBuilder::withSecurityAttributes(LPSECURITY_ATTRIBUTES securityAttributes)
{
    this->securityAttributes = securityAttributes;
    return *this;
}