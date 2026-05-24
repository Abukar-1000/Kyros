#include "../../include/Process/Metadata/ProcessMetadata.h"

ProcessMetadata::ProcessMetadata(const std::string& otherStr, DWORD pid, bool running)
{
    this->pid = static_cast<uint32_t>(pid);
    this->running = running ? 1 : 0;

    size_t safeLenth = 0;

    if (otherStr.size() < sizeof(this->name) - 1)
    {
        safeLenth = otherStr.size();
    }
    else
    {
        safeLenth = sizeof(this->name) - 1;
    }

    otherStr.copy(this->name, safeLenth);
    this->name[safeLenth] = '\0';
}

std::string ProcessMetadata::toString()
{
    return "Process: { name: " + std::string(this->name) 
            + ", pid: " + std::to_string(this->pid) 
            + ", running: " + std::to_string(this->running) + " }";
}