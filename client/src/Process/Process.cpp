#include "../../include/Process/Process.h"


Process::Process() 
:   processId(0), 
    processHandle(INVALID_HANDLE_VALUE), 
    running(false) 
{
    processHandle = this->getProcessHandle();
    if (processHandle != INVALID_HANDLE_VALUE)
    {
        this->processName = this->setProcessName();
    }
}

Process::Process(DWORD processId) 
:   processId(processId), 
    processHandle(INVALID_HANDLE_VALUE), 
    running(false) 
{
    processHandle = this->getProcessHandle();
    if (processHandle != INVALID_HANDLE_VALUE)
    {
        this->processName = this->setProcessName();
    }
}

std::string Process::setProcessName(void)
{
    try
    {
        wchar_t nameBuff[MAX_PATH];
        DWORD nameSize = MAX_PATH;
        bool success = QueryFullProcessImageNameW(processHandle, 0, nameBuff, &nameSize);
        if (!success)
        {
            return "[UNKNOWN]";
        }

        std::wstring wideCharName(nameBuff);
        size_t nameLength = std::wcstombs(nullptr, wideCharName.c_str(), 0);
        std::string _name(nameLength, '\0');
        std::wcstombs(&_name[0], wideCharName.c_str(), nameLength);
        return this->parseName(_name);
    }
    catch(const std::exception& e)
    {
        return "[UNKNOWN]";
    }
}

void Process::deleteProcess(void)
{
    CloseHandle(processHandle);
}

bool Process::kill()
{
    try
    {
        bool isTerminated = TerminateProcess(processHandle, 0);
        this->running = isTerminated;
        return isTerminated;
    }
    catch(const std::exception& e)
    {
        // Add loggine here
        this->running = true;
        return false;
    }
    
}

HANDLE Process::getProcessHandle(void) 
{
    HANDLE handle = INVALID_HANDLE_VALUE;
    try 
    {
        handle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
    }
    catch (const std::exception& e) 
    {
        try 
        {
            handle = OpenProcess(PROCESS_TERMINATE, false, processId);
        }
        catch (const std::exception& e)
        {
            handle = INVALID_HANDLE_VALUE;
        }
    }
    return handle;
}

std::string Process::parseName(std::string name)
{
    size_t lastSlashPos = name.find_last_of('\\');
    if (lastSlashPos != std::string::npos)
    {
        name = name.substr(lastSlashPos + 1);
    }
    
    size_t exePos = name.rfind(".exe");
    if (exePos != std::string::npos && exePos == name.length() - 4)
    {
        name = name.substr(0, exePos);
    }

    return name;
}
