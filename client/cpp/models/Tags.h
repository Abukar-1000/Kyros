#ifndef TAGS_H
#define TAGS_H
#include <cstdint>
#include <type_traits>

namespace Models::Process::InterProcessCom
{
    constexpr uint16_t DURATIVE_COMMAND = static_cast<uint16_t>(1) << ( ( sizeof(uint16_t) * 16 ) - 1 );
    enum class Tag : uint16_t
    {
        COMMAND_LIST_PROCESSES = 0,
        COMMAND_KILL_PROCESS = 1,
        COMMAND_KILL_PROCESS_WITH_DURATION = DURATIVE_COMMAND & 2,
        COMMAND_PAUSE_BGWORKER = 3,
        COMMAND_RESUME_BGWORKER = 4,
        COMMAND_STOP_BGWORKER = 5,
        COMMAND_SEND_NOTIFICATION = 6,
        COMMAND_GET_ALL_DISPLAYS = 7,
        COMMAND_SWITCH_DISPLAY = 8
    };
}

#endif // TAGS_H