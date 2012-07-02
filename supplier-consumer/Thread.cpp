#include "Thread.h"
#include <iostream>

Thread::Thread(ThreadRunner* runner, QObject* parent)
: QThread(parent)
, m_runner(runner)
{
}

Thread::~Thread()
{
}

void Thread::lock()
{
  m_lock.lock();
}

void Thread::unlock()
{
  m_lock.unlock();
}

bool Thread::trylock()
{
  return m_lock.tryLock();
}

void Thread::run()
{
  // The idea here is that if another thread locks this thread, that this loop
  // should terminate, thus terminating the execution of this thread.
  while(trylock())
  {
    m_runner->run();
    sleep(1);
    unlock();
  }
}

