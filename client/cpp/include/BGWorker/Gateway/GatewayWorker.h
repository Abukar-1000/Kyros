#ifndef GatewayWorker_H
#define GatewayWorker_H
#include "../IBGWorker.h"
#include <iostream>

class GatewayWorker : public IBGWorker
{
    private:
        Pipe pipe;
        bool connected;
        void act() override;
    public:
        GatewayWorker();
};

#endif // GatewayWorker_H