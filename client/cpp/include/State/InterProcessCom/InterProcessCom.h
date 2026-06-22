#ifndef IINTER_PROCESSCOM_H
#define IINTER_PROCESSCOM_H

template<typename T>
class IInterPorcessCom
{
    public:
        virtual void send(const T message) = 0;
        ~IInterPorcessCom() = default;
};

#endif // IINTER_PROCESSCOM_H