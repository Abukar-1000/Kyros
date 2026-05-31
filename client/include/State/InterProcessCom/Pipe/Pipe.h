#ifndef PIPE_H
#define PIPE_H
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

class Pipe
{
    private:
        HANDLE handle;
        std::wstring name;
        DWORD openMode;
        DWORD pipeMode;
        size_t maxInstances;
        size_t inBufferSize;
        size_t outBufferSize;
        size_t defaultTimeout;
        LPSECURITY_ATTRIBUTES securityAttributes;
        bool sendBytes(const std::byte* buffer, size_t size);
        bool sendString(const char* buffer, size_t size);
        public:
        Pipe(
            std::wstring name,
            DWORD openMode,
            DWORD pipeMode,
            size_t maxInstances,
            size_t inBufferSize,
            size_t outBufferSize,
            size_t defaultTimeout,
            LPSECURITY_ATTRIBUTES securityAttributes
        );
        ~Pipe() = default;
        bool connect(void);
        
        template<typename K>
        K receive(void);
        
        template<typename K>
        K receiveBytes(void);

        template<typename T>
        bool send(T data);
        
        bool hasData(void);
        
        void close(void);
};


template<typename K>
K Pipe::receiveBytes(void)
{
    bool success = true;
    DWORD bytesRead = 0;
    K buffer;

    if (this->handle == INVALID_HANDLE_VALUE)
    {
        /* logg */
        return buffer;
    }

    ZeroMemory(&buffer, sizeof(K)); 
    size_t totalBytes = sizeof(K);
    size_t bytesReceived = 0;
    DWORD chunkBytesRead = 0;

    std::byte* bufferPtr = reinterpret_cast<std::byte*>(&buffer);
    int i = 0;
    while (bytesReceived < totalBytes)
    {
        chunkBytesRead = 0;
        bool isSuccess = ReadFile(
            this->handle,
            bufferPtr + bytesReceived,
            static_cast<DWORD>(totalBytes - bytesReceived),
            &chunkBytesRead,
            NULL
        );
        
        success = success && isSuccess;
        if (!isSuccess)
        {
            /* logg */
            break;
        }

        if (chunkBytesRead == 0)
        {
            /* logg */
            std::cout << "No more data to read, breaking loop. " 
            << bytesReceived  << " / "<< totalBytes << std::endl;
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

    int i = 0;
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
        
        std::cout << "["
        << i++ << "] " 
        << "Read: " << chunkBytesRead 
        << " Total: " << totalBytes << std::endl;
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

    if constexpr (std::is_same<T, std::string>::value)
    {
        success = this->sendString(data.c_str(), data.size());
    }
    else if constexpr (std::is_same<T, std::vector<std::byte>>::value)
    {
        success = this->sendBytes(data.data(), data.size());
    }
    else
    {
        success = WriteFile(
            this->handle,
            &data,
            sizeof(T),
            &bytesWritten,
            NULL
        );
    }

    if (!success)
    {
        /* logg */
    }

    return success;
}
#endif // PIPE_H