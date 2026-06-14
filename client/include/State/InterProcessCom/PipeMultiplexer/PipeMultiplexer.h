#ifndef PIPE_MULTIPLEXER_H
#define PIPE_MULTIPLEXER_H
#include <memory>
#include <vector>
#include "../PipeBuilder/PipeBuilder.h"
#include "../Pipe/Pipe.h"
using Pipes = std::unique_ptr<std::vector<Pipe>>;

class PipeMultiplexer {
    protected:
        std::vector<size_t> positions;
        Pipes pipes;
    public:
        PipeMultiplexer();
        PipeMultiplexer(std::vector<Pipe>& pipes);
        ~PipeMultiplexer() = default;
        void setPipeCount(size_t count);
        void markReadyPipes(void);
        void dispatch(void);
};

#endif 