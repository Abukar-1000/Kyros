#ifndef BGWORKER_PARAMS_H
#define BGWORKER_PARAMS_H

class BGWorkerParams
{
    public:
        BGWorkerParams() = default;
        ~BGWorkerParams() = default;
        bool running;
        bool paused;
};

#endif // BGWORKER_PARAMS_H