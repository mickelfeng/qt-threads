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
  DEBUG,
  INFO,
  WARN,
  ERROR,
  CRITICAL
};

class LogStream
{
  public:
    LogStream& operator<< (const QString& str);
    LogStream& operator() (LogLevel level, LogTags tags);

    static const QString& toString(LogLevel level);
    static const QString& toString(LogTag tag);
    static QStringList toStringList(LogTags tags);

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
    static void log(LogLevel level, const QString& message);
    static void log(LogLevel level, LogTags tags, const QString& message);

    static LogRunnable* getInstance();

  private:
    LogRunnable();

    void log(std::unique_ptr<LogPacket>&& packet);

  private:
    static LogRunnable* g_instance;
    QFile m_logfile;
    QTextStream m_stream;
};

#define LOG_DEBUG(msg) do {LogRunnable::log(DEBUG,(msg));} while(0)
#define LOG_DEBUG_TAG(tags,msg) do {LogRunnable::log(DEBUG,(tags),(msg));} while(0)
#define LOG_INFO(msg) do {LogRunnable::log(INFO,(msg));} while(0)
#define LOG_INFO_TAG(tags,msg) do {LogRunnable::log(INFO,(tags),(msg));} while(0)
#define LOG_WARN(msg) do {LogRunnable::log(WARN,(msg));} while(0)
#define LOG_WARN_TAG(tags,msg) do {LogRunnable::log(WARN,(tags),(msg));} while(0)
#define LOG_ERROR(msg) do {LogRunnable::log(ERROR,(msg));} while(0)
#define LOG_ERROR_TAG(tags,msg) do {LogRunnable::log(ERROR,(tags),(msg));} while(0)
#define LOG_CRITICAL(msg) do {LogRunnable::log(CRITICAL,(msg));} while(0)
#define LOG_CRITICAL_TAG(tags,msg) do {LogRunnable::log(CRITICAL,(tags),(msg));} while(0)

#endif // LOGRUNNABLE_H

