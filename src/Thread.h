#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include <string>

/**
 *
 */
class Thread : public QThread
{
  Q_OBJECT;

  public:
    Thread(const std::string& output, QObject* parent = 0);
    ~Thread();

    void lock();
    void unlock();
    bool trylock();

  protected:
    virtual void run();

  private:
    QMutex m_lock;
    std::string m_output;
};

#endif // THREAD_H

