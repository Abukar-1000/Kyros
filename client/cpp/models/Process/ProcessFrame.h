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
        uint8_t isRunning;

        void withValues(uint32_t processId, const char* processName, bool isRunning = true)
        {
            this->processId = processId;
            strncpy(this->processName, processName, sizeof(this->processName) - 1);
            this->processName[sizeof(this->processName) - 1] = '\0';
            this->isRunning = isRunning;
        }
    };
}

#endif // PROCESS_FRAME_H