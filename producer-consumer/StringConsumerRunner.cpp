#include "StringConsumerRunner.h"
#include <iostream>
#include <unistd.h>

StringConsumerRunner::StringConsumerRunner(
    std::shared_ptr<StringConsumer>& consumer, 
    const std::string& str) 
  : m_str(str)
  , m_consumer(consumer)
{
}

void StringConsumerRunner::run()
{
  std::cout << "POP ";
  std::unique_ptr<std::string> value(m_consumer->pop());
  if (value.get())
  {
    std::cout << *value << std::endl;
  }
  else
  {
    std::cout << m_str << std::endl;
  }
  sleep(rand() % MAX_DURATION + 1);
}
