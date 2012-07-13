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
: QApplication(argc, argv)
{
  std::vector<int> data(100);
  for (size_t i = 1; i < data.size(); ++i)
  {
    data[i] = i;
  }

  PrintResult* result = new PrintResult(this);
  Processor* processor = new Processor(this);

  result->setFuture(QtConcurrent::run(boost::bind(&Processor::process, processor, data)));

  std::cout << "sup\n";

  QTimer* timer = new QTimer(this);
  timer->setInterval(5000);
  timer->start();

  connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

void Application::timeout()
{
  QThreadPool::globalInstance()->waitForDone();
  qApp->quit();
}

