#ifndef LOGRUNNABLE_H
#define LOGRUNNABLE_H

#include <QRunnable>

/**
 *
 */
class LogRunnable : public QRunnable
{
  public:
    virtual void run();

    static void create();
    static void destroy();
    static void log(const char* msg);

    static LogRunnable* getInstance();

  private:
    LogRunnable();

  private:
    static LogRunnable* g_instance;
};

#endif // LOGRUNNABLE_H

