#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QMutex>
#include <QMutexLocker>
#include <memory>
#include "Consumer.h"

template <typename T>
class Supplier
{
  public:
    explicit Supplier(std::shared_ptr<Consumer<T>>& consumer) : m_consumer(consumer)
    {
    }

    void push(T* data)
    {
      QMutexLocker locker(&m_mutex);
      std::shared_ptr<Consumer<T>> consumer = m_consumer.lock();
      if (consumer)
        consumer->push(data);
    }

    void push(std::unique_ptr<T>& data)
    {
      QMutexLocker locker(&m_mutex);
      std::shared_ptr<Consumer<T>> consumer = m_consumer.lock();
      if (consumer)
        consumer->push(data);
    }

  private:
    std::weak_ptr<Consumer<T>> m_consumer;
    QMutex m_mutex;
};

#endif // SUPPLIER_H

