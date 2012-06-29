#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include <string>

/**
 * A simple thread class that contains a thread-locking mechanism.
 */
class Thread : public QThread
{
  Q_OBJECT;

  public:
    /**
     * Creates a Thread object, and initializes the output string.
     *
     * @param output - the string that will be output when the thread is run
     * @param parent - the parent object of this thread
     */
    Thread(const std::string& output, QObject* parent = 0);

    /**
     * Destroys this thread.
     */
    ~Thread();

    /**
     * Requests the lock on this thread.
     */
    void lock();

    /**
     * Releases the lock on this thread.
     */
    void unlock();

    /**
     * Tries to acquire the lock on this thread. If the thread is already
     * locked, this function immediately returns FALSE, other the lock is
     * acquired and TRUE is returned.
     *
     * @return a boolean indicating whether the thread was locked or not.
     */
    bool trylock();

  protected:
    /**
     * This function is executed when start() is called on the thread.
     */
    virtual void run();

  private:
    QMutex m_lock;
    std::string m_output;
};

#endif // THREAD_H

