#ifndef IPROCESS_VISITEE_H
#define IPROCESS_VISITEE_H
#include "../Visitors/IProcessVisitor.h"

class IProcessVisitee
{
    public:
        virtual ~IProcessVisitee() = default;
        virtual void accept(IProcessVisitor& visitor) = 0;
};

#endif // IPROCESS_VISITEE_H