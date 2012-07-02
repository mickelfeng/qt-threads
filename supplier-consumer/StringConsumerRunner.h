#ifndef STRINGCONSUMERRUNNER_H
#define STRINGCONSUMERRUNNER_H

#include "Thread.h"
#include "Consumer.h"
#include <string>
#include <memory>

typedef Consumer<std::string> StringConsumer;

/**
 *
 */
class StringConsumerRunner : public ThreadRunner
{
  public:
    StringConsumerRunner(std::shared_ptr<StringConsumer>& consumer, 
      const std::string& str); 

    virtual void run();

  private:
    std::string m_str;
    std::shared_ptr<StringConsumer> m_consumer;

    static const int MAX_DURATION = 3;
};

#endif // STRINGCONSUMERRUNNER_H

