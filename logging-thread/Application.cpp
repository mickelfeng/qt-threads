#include "Application.h"
#include <QTimer>
#include <QThreadPool>
#include "LogRunnable.h"
#include "SpamRunnable.h"

namespace
{
  const unsigned int NUM_SPAM_THREADS = 2;
}

Application::Application(int argc, char** argv)
: QApplication(argc, argv)
{
  LogRunnable::create();

  QThreadPool::globalInstance()->start(LogRunnable::getInstance());

  for (unsigned int i = 0; i < NUM_SPAM_THREADS; ++i)
  {
    m_threads.push_back(new SpamRunnable);
    QThreadPool::globalInstance()->tryStart(m_threads.back());
  }

  // Create a timer to terminate this application
  QTimer* timer = new QTimer(this);
  timer->setInterval(1000);
  timer->setSingleShot(true);

  // Connect the timer to the applications timeout slot
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

  // Start the timers
  timer->start();
}

void Application::timeout()
{
  for (unsigned int i = 0; i < NUM_SPAM_THREADS; ++i)
    m_threads[i]->stop();

  QThreadPool::globalInstance()->waitForDone();
  LogRunnable::destroy();
  qApp->quit();
}

