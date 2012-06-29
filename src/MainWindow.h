#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Thread;

class MainWindow : public QMainWindow
{
  Q_OBJECT;

  public:
    MainWindow();

    void start();

  public slots:
    void lockA();
    void lockB();

  private:
    Thread* workerA;
    Thread* workerB;
};

#endif // MAINWINDOW_H

