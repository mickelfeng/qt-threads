#include "Consumer.h"
#include <iostream>

Consumer::Consumer()
{
}

void Consumer::log(const char* str)
{
  std::unique_ptr<std::string> data(new std::string(str));
  getInstance()->m_queue.push(data);
}

Consumer* Consumer::getInstance()
{
  static Consumer* consumer = new Consumer;
  return consumer;
}

void Consumer::run()
{
  std::cout << "POP ";
  std::unique_ptr<std::string> data = std::move(m_queue.pop());
  if (data)
  {
    std::cout << *data << std::endl;
  }
  else
  {
    std::cout << "null" << std::endl;
  }
}

void Consumer::flush()
{
  while (true)
  {
    std::unique_ptr<std::string> data = std::move(m_queue.pop());
    if (!data)
      break;
    std::cout << "POP " << *data << std::endl;
  }
}

