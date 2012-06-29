#include "Thread.h"
#include <iostream>

Thread::Thread(const std::string& output, QObject* parent)
: QThread(parent)
, m_output(output)
{
  std::cerr << "Started " << this << std::endl;
}

Thread::~Thread()
{
  std::cerr << "Destroyed " << this << std::endl;
}

void Thread::lock()
{
  std::cout << "[" << this << "] lock() called" << std::endl;
  m_lock.lock();
}

void Thread::unlock()
{
  std::cout << "[" << this << "] unlock() called" << std::endl;
  m_lock.unlock();
}

bool Thread::trylock()
{
  std::cout << "[" << this << "] trylock() called" << std::endl;
  return m_lock.tryLock();
}

void Thread::run()
{
  std::cout << "[" << this << "] entered run()" << std::endl;
  while(trylock())
  {
    std::cout << m_output << std::endl;
    QThread::sleep(1);
    unlock();
  }
  std::cout << "[" << this << "] exited run()" << std::endl;
}

