#include "../../include/Command/Visitors/ProcessVisitor.h"

ProcessVisitor::ProcessVisitor() {}

void ProcessVisitor::visit(DeleteCommand& visitee)
{
    std::cout << "Visiting DeleteCommand" << std::endl;
    visitee.execute();
}