#ifndef IOBSERVER_H
#define IOBSERVER_H
#include <memory>

template<typename T>
class IObserver {
private:
    std::shared_ptr<IObserver<T>> self;
public:
    virtual ~IObserver() = default;
    virtual void update(T value) = 0;
};

#endif // IOBSERVER_H