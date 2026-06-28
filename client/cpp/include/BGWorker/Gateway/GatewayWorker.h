#ifndef GatewayWorker_H
#define GatewayWorker_H
#include "../../../Command/Process/DurativeRequest/DurativeRequest.h"
#include "../../../models/Object/Object.h"
#include "../../../models/Tags.h"
#include "../IBGWorker.h"
#include <iostream>

namespace Frames = Models::Process::InterProcessCom;
class GatewayWorker : public IBGWorker
{
    private:
        Pipe pipe;
        bool connected;
        void act() override;
    public:
        GatewayWorker();
        void queueRequest(Object& request);
};

#endif // GatewayWorker_H