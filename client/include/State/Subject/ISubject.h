#ifndef ISUBJECT_H
#define ISUBJECT_H
#include <memory>
#include "../Observer/IObserver.h"

template<typename T>
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver<T>> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver<T>> observer) = 0;
    virtual void notify() = 0;
};

#endif // ISUBJECT_H