#ifndef LOGRUNNABLE_H
#define LOGRUNNABLE_H

#include <QRunnable>
#include <QFile>
#include <QTextStream>
#include "LogPacket.h"

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

