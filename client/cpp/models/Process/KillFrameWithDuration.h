#ifndef KILL_FRAME_WITH_DURATION_H
#define KILL_FRAME_WITH_DURATION_H
#include <cstdint>
#include <cstring>
#include "../Tags.h"
#include "KillFrame.h"

namespace Models::Process::InterProcessCom
{
    struct KillFrameWithDuration: public KillFrame
    {
        uint16_t id = static_cast<uint16_t>(Tag::COMMAND_KILL_PROCESS_WITH_DURATION);
        uint32_t duration;

        void withValues(uint32_t processId, const char* processName, uint32_t duration)
        {
            this->duration = duration;
            this->processId = processId;
            strncpy(this->processName, processName, sizeof(this->processName) - 1);
            this->processName[sizeof(this->processName) - 1] = '\0'; 
        }
    };
}

#endif // KILL_FRAME_WITH_DURATION_H