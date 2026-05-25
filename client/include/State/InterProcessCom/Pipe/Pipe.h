#ifndef PIPE_H
#define PIPE_H
#include <windows.h>
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

        template<typename T>
        bool send(T data);
        
        template<typename K>
        K receive(void);

        void close(void);
};

#endif // PIPE_H