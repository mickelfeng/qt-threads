#include "Application.h"
#include <QTimer>
#include "StringConsumerRunner.h"
#include "StringSupplierRunner.h"

Application::Application(int argc, char** argv)
: QApplication(argc, argv)
{
  std::shared_ptr<StringConsumer> consumer(new StringConsumer);
  StringSupplier* supplierX = new StringSupplier(consumer);
  StringSupplier* supplierY = new StringSupplier(consumer);
  ThreadRunner* runnerA = new StringConsumerRunner(consumer, "tic");
  ThreadRunner* runnerB = new StringSupplierRunner(supplierX, "tocX");
  ThreadRunner* runnerC = new StringSupplierRunner(supplierY, "tocY");

  m_threads.push_back(std::move(std::unique_ptr<Thread>(new Thread(runnerA))));
  m_threads.push_back(std::move(std::unique_ptr<Thread>(new Thread(runnerB))));
  m_threads.push_back(std::move(std::unique_ptr<Thread>(new Thread(runnerC))));

  // Start up the threads
  for (auto thread = m_threads.begin(); thread != m_threads.end(); ++thread)
    (*thread)->start();

  // Create a timer to terminate this application
  QTimer* timer = new QTimer(this);
  timer->setInterval(10000);
  timer->setSingleShot(true);

  // Connect the timer to the applications timeout slot
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

  // Start the timers
  timer->start();
}

void Application::timeout()
{
  for (auto thread = m_threads.begin(); thread != m_threads.end(); ++thread)
  {
    (*thread)->lock();
    (*thread)->wait();
    (*thread)->unlock();
  }
  
  qApp->quit();
}

