#ifndef IPROCESS_VISITOR_H
#define IPROCESS_VISITOR_H
class DeleteCommand;

class IProcessVisitor
{
    public:
        ~IProcessVisitor() = default;
        virtual void visit(DeleteCommand& visitee) = 0;
};

#endif // IPROCESS_VISITOR_H