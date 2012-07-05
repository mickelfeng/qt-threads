#include "Producer.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Consumer.h"

Producer::Producer(const std::string& str)
: m_str(str)
{
}

void Producer::run()
{
  usleep(rand() & 1000000);
  Consumer::log(m_str.c_str());
  std::cerr << "PUSH " << m_str << std::endl;
}

