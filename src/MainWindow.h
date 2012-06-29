#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Thread;

/**
 * A simple window that acts as a container and interface for a couple of worker
 * threads.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT;

  public:
    /**
     * Default constructor. Creates the worker threads and connects them to the
     * quit() slot of the new instance of this class.
     */
    MainWindow();

    /**
     * Starts the execution of the worker threads.
     */
    void start();

  public slots:
    /**
     * Requests the lock on worker A, effectively terminating the execution of
     * the thread.
     */
    void lockA();

    /**
     * Requests the lock on worker B, effectively terminating the execution of
     * the thread.
     */
    void lockB();

    /**
     * If both of the worker threads are finished when this function is invoked,
     * the application quits.
     */
    void quit();

  private:
    Thread* workerA;
    Thread* workerB;
};

#endif // MAINWINDOW_H

