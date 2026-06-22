#ifndef PROCESS_VISITOR_H
#define PROCESS_VISITOR_H
#include "../Process/DeleteCommand.h"
#include "IProcessVisitor.h"

class ProcessVisitor : public IProcessVisitor
{
    public:
        ProcessVisitor();
        ~ProcessVisitor() = default;
        void visit(DeleteCommand& visitee) override;
};

#endif // PROCESS_VISITOR_H
