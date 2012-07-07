#include "LogRunnable.h"
#include <QMutexLocker>
#include <QMutex>
#include <QDateTime>
#include <iostream>

namespace
{
  QMutex lock(QMutex::Recursive);
}

LogRunnable* LogRunnable::g_instance = 0;

void LogRunnable::run()
{
}

void LogRunnable::create()
{
  QMutexLocker locker(&lock);
  if (!g_instance)
  {
    g_instance = new LogRunnable;
    LOG_INFO("log start");
  }
}

void LogRunnable::log(const QString& severity, const QString& message)
{
  QMutexLocker locker(&lock);
  LogRunnable* instance = getInstance();
  if (instance)
  {
    std::unique_ptr<LogPacket> packet(new LogPacket);
    packet->severity = severity;
    packet->message = message;
    packet->timestamp = QDateTime::currentMSecsSinceEpoch();
    instance->log(std::move(packet));
  }
}

void LogRunnable::log(std::unique_ptr<LogPacket>&& packet)
{
  m_stream << "{";
  m_stream << "timestamp:" << packet->timestamp << ", ";
  m_stream << "severity:\"" << packet->severity << "\", ";
  m_stream << "tags:[], ";
  m_stream << "message:\"" << packet->message << "\"";
  m_stream << "}";
  endl(m_stream);
  m_stream.flush();
}

void LogRunnable::destroy()
{
  QMutexLocker locker(&lock);
  LOG_INFO("log end");
  delete g_instance;
  g_instance = 0;
}

LogRunnable* LogRunnable::getInstance()
{
  return g_instance;
}

LogRunnable::LogRunnable() 
: QRunnable()
{
  setAutoDelete(false);

  QTextStream stream(new QString);

  stream << "session_";
  stream << QDateTime::currentDateTime().currentMSecsSinceEpoch();
  stream << ".log";

  m_logfile.setFileName(*stream.string());
  m_logfile.open(QIODevice::WriteOnly);

  m_stream.setDevice(&m_logfile);
}

LogRunnable::~LogRunnable()
{
  m_logfile.close();
}

LogStream& LogStream::operator<< (const QString& str)
{
  switch (m_level)
  {
    case DEBUG:     LogRunnable::log("DEBUG", str);     break;
    case INFO:      LogRunnable::log("INFO", str);      break;
    case WARN:      LogRunnable::log("WARN", str);      break;
    case ERROR:     LogRunnable::log("ERROR", str);     break;
    case CRITICAL:  LogRunnable::log("CRITICAL", str);  break;
  }
  return *this;
}

LogStream& LogStream::operator() (LogLevel level, LogTags tags)
{
  m_level = level;
  m_tags = tags;
  return *this;
}

