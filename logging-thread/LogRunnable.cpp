#include "LogRunnable.h"
#include <QMutexLocker>
#include <QMutex>
#include <iostream>

LogRunnable* LogRunnable::g_instance = 0;

QMutex mutex;

void LogRunnable::run()
{
  std::clog << "done.\n";
}

void LogRunnable::create()
{
  if (!g_instance)
  {
    g_instance = new LogRunnable;
    std::clog << "LogRunnable created\n";
  }
}

void LogRunnable::log(std::unique_ptr<LogPacket>&& packet)
{
  QMutexLocker locker(&mutex);
  std::clog << "[" << packet->timestamp<< "] " << packet->severity 
  std::clog << ":" << packet->message << std::endl;
}

void LogRunnable::destroy()
{
  delete g_instance;
  g_instance = 0;
  std::clog << "LogRunnable destroyed\n";
}

LogRunnable* LogRunnable::getInstance()
{
  if (!g_instance)
    create();

  return g_instance;
}

LogRunnable::LogRunnable() : QRunnable()
{
  setAutoDelete(false);
}

