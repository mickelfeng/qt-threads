#include "MainWindow.h"
#include "Thread.h"

MainWindow::MainWindow() : QMainWindow()
, workerA(new Thread("tic"))
, workerB(new Thread("toc"))
{
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
