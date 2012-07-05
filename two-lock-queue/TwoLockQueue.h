#ifndef TWOLOCKQUEUE_H
#define TWOLOCKQUEUE_H

#include <memory>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

/**
 *
 */
template <typename T>
class TwoLockQueue
{
  public:
    TwoLockQueue()
    {
      m_head = new Node;
      m_head->next = 0;
      m_tail = m_head;
    }

    ~TwoLockQueue()
    {
      delete m_head;
    }

    void push(std::unique_ptr<T> && data)
    {
      Node* node = new Node;
      node->next = 0;
      node->data = std::move(data);

      QMutexLocker locker(&m_tailLock);
      m_tail->next = node;
      m_tail = node;
    }

    std::unique_ptr<T> pop()
    {
      std::unique_ptr<T> result;

      QMutexLocker locker(&m_headLock);
      Node* node = m_head;
      Node* new_head = node->next;
      if (new_head)
      {
        result.reset(new_head->data.release());
        m_head = new_head;
        delete node;
      }

      return result;
    }

  private:
    struct Node
    {
      Node* next;
      std::unique_ptr<T> data;
    };

    Node* m_head;
    Node* m_tail;
    QMutex m_headLock;
    QMutex m_tailLock;
};

#endif // TWOLOCKQUEUE_H

