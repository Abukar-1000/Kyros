#ifndef TAGS_H
#define TAGS_H
#include <cstdint>

namespace Models::Process::InterProcessCom
{
    enum class Tag : uint16_t
    {
        COMMAND_LIST_PROCESSES,
        COMMAND_KILL_PROCESS,
        COMMAND_PAUSE_BGWORKER,
        COMMAND_RESUME_BGWORKER,
        COMMAND_STOP_BGWORKER,
        COMMAND_SEND_NOTIFICATION,
        COMMAND_GET_ALL_DISPLAYS,
        COMMAND_SWITCH_DISPLAY
    };
}

#endif // TAGS_H