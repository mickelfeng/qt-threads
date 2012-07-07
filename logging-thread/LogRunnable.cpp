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

void LogRunnable::log(const char* msg)
{
  QMutexLocker locker(&mutex);
  std::clog << msg << std::endl;
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

