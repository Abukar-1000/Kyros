#ifndef PROCESS_METADATA_H
#define PROCESS_METADATA_H
#include <string>
#include <cstdint>
#include <windows.h>

class ProcessMetadata
{
    public:
        char name[256];
        uint32_t pid;
        uint8_t running;
        ProcessMetadata(const std::string& name, DWORD pid, bool running);
        std::string toString();
        ~ProcessMetadata() = default;
};

#endif // PROCESS_METADATA_H