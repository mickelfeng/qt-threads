#include "SpamRunnable.h"
#include <unistd.h>
#include <cstdlib>
#include "LogRunnable.h"

namespace
{
  const size_t NUM_MESSAGES = 4;
  const char* message[NUM_MESSAGES] = {"fee","fie","foe","fum"};
}

SpamRunnable::SpamRunnable() 
  : QRunnable()
{
}

void SpamRunnable::run()
{
  while (m_mutex.tryLock())
  {
    std::unique_ptr<LogPacket> packet 
      = std::move(createSimplePacket("DEBUG",message[rand() % NUM_MESSAGES]));
    LogRunnable::log(std::move(packet));
    m_mutex.unlock();
  }
}

void SpamRunnable::stop()
{
  m_mutex.lock();
}

