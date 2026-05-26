#ifndef PROCESS_FRAME_H
#define PROCESS_FRAME_H
#include <cstdint>
#include <cstring>

namespace Models::Process::InterProcessCom
{
    struct ProcessFrame
    {
        uint32_t processId;
        char processName[256];

        void withValues(uint32_t processId, const char* processName)
        {
            this->processId = processId;
            strncpy(this->processName, processName, sizeof(this->processName) - 1);
            this->processName[sizeof(this->processName) - 1] = '\0'; // Ensure null-termination
        }
    };
}

#endif // PROCESS_FRAME_H