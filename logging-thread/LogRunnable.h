#ifndef LOGRUNNABLE_H
#define LOGRUNNABLE_H

#include <QRunnable>
#include <QFile>
#include <QTextStream>
#include "LogPacket.h"

enum LogTag
{
  THREAD  = 1 << 0,
  GUI     = 1 << 1
};

Q_DECLARE_FLAGS(LogTags, LogTag);
Q_DECLARE_OPERATORS_FOR_FLAGS(LogTags);

enum LogLevel
{
  DEBUG     = 1 << 0,
  INFO      = 1 << 1,
  WARN      = 1 << 2,
  ERROR     = 1 << 3,
  CRITICAL  = 1 << 4
};


class LogStream
{
  public:
    LogStream& operator<< (const QString& str);
    LogStream& operator() (LogLevel level, LogTags tags);

  private:
    LogLevel m_level;
    LogTags m_tags;
};

/**
 *
 */
class LogRunnable : public QRunnable
{
  public:
    virtual ~LogRunnable();

    virtual void run();

    static void create();
    static void destroy();
    static void log(const QString& severity, const QString& message);

    static LogRunnable* getInstance();

  private:
    LogRunnable();

    void log(std::unique_ptr<LogPacket>&& packet);

  private:
    static LogRunnable* g_instance;
    QFile m_logfile;
    QTextStream m_stream;
};

#define LOG_DEBUG(msg) do {LogRunnable::log("DEBUG",(msg));} while(0)
#define LOG_INFO(msg) do {LogRunnable::log("INFO",(msg));} while(0)

#endif // LOGRUNNABLE_H

