#ifndef CONSUMER_H
#define CONSUMER_H

#include <QMutex>
#include <QMutexLocker>
#include <memory>
#include <iostream>

template <typename> class Supplier;

template <typename T>
class Consumer
{
  public:
    template <typename> friend class Supplier;

    std::unique_ptr<T> pop()
    {
      QMutexLocker locker(&m_mutex);
      return std::unique_ptr<T>(m_data.release());
    }

    bool empty() const
    {
      QMutexLocker locker(&m_mutex);
      return m_data.empty();
    }

  private:
    void push(T* data)
    {
      QMutexLocker locker(&m_mutex);
      m_data.reset(data);
    }

    void push(std::unique_ptr<T>&& data)
    {
      QMutexLocker locker(&m_mutex);
      m_data.reset(data);
    }

  private:
    QMutex m_mutex;
    std::unique_ptr<T> m_data;
};

#endif // CONSUMER_H

