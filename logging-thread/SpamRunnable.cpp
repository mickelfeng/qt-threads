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
    LOG_DEBUG(message[rand() % NUM_MESSAGES]);
    m_mutex.unlock();
  }
}

void SpamRunnable::stop()
{
  m_mutex.lock();
}

