#ifndef SPAMRUNNABLE_H
#define SPAMRUNNABLE_H

#include <QRunnable>
#include <QMutex>

/**
 *
 */
class SpamRunnable : public QRunnable
{
  public:
    SpamRunnable();
    virtual void run();

    void stop();

  private:
    QMutex m_mutex;
    const char* m_msg;
};

#endif // SPAMRUNNABLE_H

