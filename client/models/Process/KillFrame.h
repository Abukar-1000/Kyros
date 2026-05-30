#ifndef KiLL_FRAME_H
#define KiLL_FRAME_H
#include <cstdint>
#include <cstring>

namespace Models::Process::InterProcessCom
{
    struct KillFrame
    {
        uint32_t processId;
        char processName[256];

        void withValues(uint32_t processId, const char* processName)
        {
            this->processId = processId;
            strncpy(this->processName, processName, sizeof(this->processName) - 1);
            this->processName[sizeof(this->processName) - 1] = '\0'; 
        }
    };
}

#endif // KiLL_FRAME_H