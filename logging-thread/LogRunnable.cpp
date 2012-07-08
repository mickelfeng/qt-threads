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

void LogRunnable::log(LogLevel severity, const QString& message)
{
  QMutexLocker locker(&lock);
  LogRunnable* instance = getInstance();
  if (instance)
  {
    std::unique_ptr<LogPacket> packet(new LogPacket);
    packet->severity = LogStream::toString(severity);
    packet->message = message;
    packet->timestamp = QDateTime::currentMSecsSinceEpoch();
    instance->log(std::move(packet));
  }
}

void LogRunnable::log(LogLevel severity, LogTags tags, const QString& message)
{
  QMutexLocker locker(&lock);
  LogRunnable* instance = getInstance();
  if (instance)
  {
    std::unique_ptr<LogPacket> packet(new LogPacket);
    packet->severity = LogStream::toString(severity);
    packet->message = message;
    packet->timestamp = QDateTime::currentMSecsSinceEpoch();
    packet->tags = LogStream::toStringList(tags);
    instance->log(std::move(packet));
  }
}

void LogRunnable::log(std::unique_ptr<LogPacket>&& packet)
{
  m_stream << "{";
  m_stream << "timestamp:" << packet->timestamp << ", ";
  m_stream << "severity:\"" << packet->severity << "\", ";
  m_stream << "tags:[";
  if (packet->tags.size() > 0)
  {
    m_stream << "\"" << packet->tags[0] << "\"";
    for (size_t i = 1; i < packet->tags.size(); ++i)
      m_stream << ", \"" << packet->tags[i] << "\"";
  }
  m_stream << "], ";
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
  LogRunnable::log(m_level, m_tags, str);
  return *this;
}

LogStream& LogStream::operator() (LogLevel level, LogTags tags)
{
  m_level = level;
  m_tags = tags;
  return *this;
}

QStringList LogStream::toStringList(LogTags tags)
{
  QStringList strings;

  if (tags.testFlag(THREAD))
    strings.append(toString(THREAD));

  if (tags.testFlag(GUI))
    strings.append(toString(GUI));

  return strings;
}

const QString& LogStream::toString(LogTag tag)
{
  const static QString strings[] = {
    QString("UNKNOWN"),
    QString("THREAD"),
    QString("GUI")
  };

  switch (tag)
  {
    case THREAD: return strings[1];
    case GUI: return strings[2];
  }

  return strings[0];
}

const QString& LogStream::toString(LogLevel level)
{
  const static QString strings[] = {
    QString("DEBUG"),
    QString("INFO"),
    QString("WARN"),
    QString("ERROR"),
    QString("CRITICAL")};

  return strings[level];
}

