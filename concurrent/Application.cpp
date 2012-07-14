#include "Application.h"
#include <vector>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <QThreadPool>
#include <QTimer>
#include <QFutureWatcher>
#include <QtConcurrentRun>
#include "PrintResult.h"
#include "Processor.h"

Application::Application(int argc, char** argv)
: QApplication(argc, argv), m_sum(0)
{
  int* data = new int[100];
  for (int i = 0; i < 100; ++i)
  {
    data[i] = i;
  }

  PrintResult* resultA = new PrintResult(this);
  PrintResult* resultB = new PrintResult(this);

  connect(resultA, SIGNAL(sum(int)), this, SLOT(accumulate(int)));
  connect(resultB, SIGNAL(sum(int)), this, SLOT(accumulate(int)));

  resultA->setFuture(QtConcurrent::run(boost::bind(&Processor::process, new Processor(this), data, 50)));
  resultB->setFuture(QtConcurrent::run(boost::bind(&Processor::process, new Processor(this), data + 50, 50)));

  std::cout << "sup\n";

  QTimer* timer = new QTimer(this);
  timer->setInterval(5000);
  timer->start();

  connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

void Application::timeout()
{
  QThreadPool::globalInstance()->waitForDone();
  std::cout << m_sum << std::endl;
  qApp->quit();
}

void Application::accumulate(int sum)
{
  m_sum += sum;
}

