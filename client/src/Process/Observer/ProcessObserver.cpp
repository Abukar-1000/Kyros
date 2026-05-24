#include "../../include/Process/Observer/ProcessObserver.h"

ProcessObserver::ProcessObserver() {}

void ProcessObserver::update(SharedProcessList value)
{
    std::cout << "Received update with " << value->size() << " processes." << std::endl;
    for (size_t i = 0; i < value->size(); i++)
    {
        std::cout << "Process " << i << ": " << value->at(i).toString() << std::endl;
        std::cout << "Metadata: " << i << " " << value->at(i).getMetadata()->toString() << "\n\n" << std::endl;
    }
} 