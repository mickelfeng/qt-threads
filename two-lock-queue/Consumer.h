#ifndef CONSUMER_H
#define CONSUMER_H

#include <string>
#include "Thread.h"
#include "TwoLockQueue.h"

/**
 *
 */
class Consumer : public ThreadRunner
{
  public:
    static Consumer* getInstance();
    static void log(const char* str);

    virtual void run();
    virtual void flush();

  private:
    Consumer();

  private:
    TwoLockQueue<std::string> m_queue;
};

#endif // CONSUMER_H

