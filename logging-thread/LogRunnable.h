#ifndef LOGRUNNABLE_H
#define LOGRUNNABLE_H

#include <QRunnable>
#include "LogPacket.h"

/**
 *
 */
class LogRunnable : public QRunnable
{
  public:
    virtual void run();

    static void create();
    static void destroy();
    static void log(std::unique_ptr<LogPacket>&& packet);

    static LogRunnable* getInstance();

  private:
    LogRunnable();

  private:
    static LogRunnable* g_instance;
};

#define LOG_DEBUG(msg) do {LogRunnable::log(createSimplePacket("DEBUG",(msg)));} while(0)

#endif // LOGRUNNABLE_H

