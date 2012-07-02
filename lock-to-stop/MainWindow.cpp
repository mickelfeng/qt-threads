#include "MainWindow.h"
#include <QCoreApplication>
#include "Thread.h"

MainWindow::MainWindow() : QMainWindow()
, workerA(new Thread("tic"))
, workerB(new Thread("toc"))
{
  connect(workerA, SIGNAL(finished()), this, SLOT(quit()));
  connect(workerB, SIGNAL(finished()), this, SLOT(quit()));
}

void MainWindow::start()
{
  workerA->start();
  workerB->start();
}

void MainWindow::lockA()
{
  workerA->lock();
}

void MainWindow::lockB()
{
  workerB->lock();
}

void MainWindow::quit()
{
  if (workerA->isFinished() && workerB->isFinished())
    qApp->quit();
}
