#include "../../../../include/State/InterProcessCom/Pipe/Pipe.h"

Pipe::Pipe()
{}

Pipe::Pipe(
    std::wstring name,
    DWORD openMode,
    DWORD pipeMode,
    size_t maxInstances,
    size_t inBufferSize,
    size_t outBufferSize,
    size_t defaultTimeout,
    LPSECURITY_ATTRIBUTES securityAttributes
)
:   name(name), 
    openMode(openMode), 
    pipeMode(pipeMode), 
    maxInstances(maxInstances), 
    inBufferSize(inBufferSize), 
    outBufferSize(outBufferSize), 
    defaultTimeout(defaultTimeout), 
    securityAttributes(securityAttributes)
{
    this->handle = CreateNamedPipeW(
        this->name.c_str(),
        this->openMode,
        this->pipeMode,
        this->maxInstances,
        this->inBufferSize,
        this->outBufferSize,
        this->defaultTimeout,
        this->securityAttributes
    );

    if (this->handle == INVALID_HANDLE_VALUE)
    {
        /* logg */
    }
}

bool Pipe::sendBytes(const std::byte* buffer, size_t size)
{
    DWORD bytesWritten = 0;
    bool success = true;
    if (this->handle == INVALID_HANDLE_VALUE)
    {
        /* logg */
        return false;
    }

    DWORD chunkBytesWritten = 0;
    while (bytesWritten < size)
    {
        chunkBytesWritten = 0;
        bool isSuccess = WriteFile(
            this->handle,
            static_cast<const char*>((void*) buffer) + bytesWritten,
            static_cast<DWORD>(size - bytesWritten),
            &chunkBytesWritten,
            NULL
        );

        success = success && isSuccess;
        if (!isSuccess)
        {
            /* logg */
            break;
        }

        bytesWritten += chunkBytesWritten;

        std::cout << "Written: " << chunkBytesWritten << " Total: " << bytesWritten << std::endl;
    }

    if (!success)
    {
        /* logg */
    }

    return success;
}

bool Pipe::sendString(const char* buffer, size_t size)
{
    DWORD bytesWritten = 0;
    bool success = true;
    if (this->handle == INVALID_HANDLE_VALUE)
    {
        /* logg */
        return false;
    }

    success = WriteFile(
        this->handle,
        buffer,
        static_cast<DWORD>(size + 1),
        &bytesWritten,
        NULL
    );

    if (!success)
    {
        /* logg */
    }

    return success;
}

void Pipe::close(void)
{
    if (this->handle != INVALID_HANDLE_VALUE)
    {
        FlushFileBuffers(this->handle);
        DisconnectNamedPipe(this->handle);
        CloseHandle(this->handle);
        this->handle = INVALID_HANDLE_VALUE;
    }
}

bool Pipe::connect(void)
{
    bool isConnected = ConnectNamedPipe(this->handle, nullptr);
    if (!isConnected)
    {
        /* logg */
        CloseHandle(this->handle);
        this->handle = INVALID_HANDLE_VALUE;
    }

    return isConnected;
}

bool Pipe::hasData(void)
{
    if (this->handle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD bytesAvailable = 0;
    DWORD bytesLeft = 0;
    bool success = PeekNamedPipe(
        this->handle,
        NULL,
        0,
        NULL,
        &bytesAvailable,
        &bytesLeft
    );

    return success && bytesAvailable > 0;
}