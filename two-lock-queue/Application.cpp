#include "Application.h"
#include <QTimer>
#include "Producer.h"
#include "Consumer.h"

Application::Application(int argc, char** argv)
: QApplication(argc, argv)
{
  ThreadRunner* consumer = Consumer::getInstance();
  ThreadRunner* producerA = new Producer("tic");
  ThreadRunner* producerB = new Producer("toc");
  m_threads.push_back(std::move(std::unique_ptr<Thread>(new Thread(producerA))));
  m_threads.push_back(std::move(std::unique_ptr<Thread>(new Thread(producerB))));

  // This is a little sneaky. Putting the consumer last means that it will be the last thread to be
  // shutdown when the application quits. This will allow it to flush the contents of the queue,
  // without the risk that the producer threads will try to push anything onto the queue afterwards.
  m_threads.push_back(std::move(std::unique_ptr<Thread>(new Thread(consumer))));

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

