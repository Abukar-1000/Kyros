#include "../../../../include/State/InterProcessCom/Pipe/Pipe.h"

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

template<typename K>
K Pipe::receive(void)
{
    bool success = true;
    DWORD bytesRead = 0;
    K buffer;

    if (this->handle == INVALID_HANDLE_VALUE)
    {
        /* logg */
        return buffer;
    }

    size_t totalBytes = sizeof(K);
    size_t bytesReceived = 0;
    DWORD chunkBytesRead = 0;

    std::byte* bufferPtr = reinterpret_cast<std::byte*>(&buffer);

    while (bytesReceived < totalBytes)
    {
        chunkBytesRead = 0;
        bool isSuccess = ReadFile(
            this->handle,
            bufferPtr + bytesReceived,
            static_cast<DWORD>(totalBytes - bytesReceived),
            &chunkBytesRead,
            nullptr
        );
        
        success = success && isSuccess;
        if (!isSuccess)
        {
            /* logg */
            break;
        }

        bytesReceived += chunkBytesRead;
    }
    
    if (!success)
    {
        /* logg */
    }

    return buffer;
}

template<typename T>
bool Pipe::send(T data)
{
    DWORD bytesWritten = 0;
    bool success = false;
    if (this->handle == INVALID_HANDLE_VALUE)
    {
        /* logg */
        return false;
    }

    if (std::is_same<T, std::string>)
    {
        const char* buffer = data.c_str();
        success = WriteFile(
            this->handle,
            data.c_str(),
            static_cast<DWORD>(data.size()),
            &bytesWritten,
            nullptr
        );
    }
    else
    {
        success = WriteFile(
            this->handle,
            &data,
            sizeof(T),
            &bytesWritten,
            nullptr
        );
    }

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
    if (this->handle == INVALID_HANDLE_VALUE)
    {
        /* logg */
        return false;
    }

    bool isConnected = ConnectNamedPipe(this->handle, nullptr);
    if (!isConnected)
    {
        /* logg */
        CloseHandle(this->handle);
        this->handle = INVALID_HANDLE_VALUE;
    }

    return isConnected;
}