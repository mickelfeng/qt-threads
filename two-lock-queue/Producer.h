#ifndef PRODUCER_H
#define PRODUCER_H

#include <string>
#include "Thread.h"

/**
 *
 */
class Producer : public ThreadRunner
{
  public:
    Producer(const std::string& str);

    virtual void run();


  private: 
    std::string m_str;
};

#endif // PRODUCER_H

