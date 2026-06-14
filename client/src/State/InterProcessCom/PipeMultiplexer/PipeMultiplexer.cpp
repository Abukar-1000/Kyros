#include "../../../../include/State/InterProcessCom/PipeMultiplexer/PipeMultiplexer.h"

PipeMultiplexer::PipeMultiplexer() 
{}

PipeMultiplexer::PipeMultiplexer(std::vector<Pipe>& pipes) 
{
    this->pipes->reserve(pipes.size());
    
    for (size_t i = 0; i < pipes.size(); ++i)
    {
        this->pipes->push_back(std::move(pipes[i]));
    }
}

void PipeMultiplexer::markReadyPipes(void)
{
    for (size_t i = 0; i < this->pipes->size(); ++i)
    {
        if (this->pipes->at(i).hasData())
        {
            this->positions.push_back(i);
        }
    }

    this->positions.push_back(NULL);
}

void PipeMultiplexer::dispatch(void)
{
    size_t i = 0;
    while (i < this->positions.size())
    {
        if (this->positions.at(i) == NULL)
        {
            break;
        }

        /* Read & Handle dispatch here */
        ++i;
    }
}

void PipeMultiplexer::setPipeCount(size_t count)
{
    this->pipes->reserve(count);
}

