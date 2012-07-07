#include "Application.h"
#include <QTimer>
#include <QThreadPool>
#include "LogRunnable.h"

Application::Application(int argc, char** argv)
: QApplication(argc, argv)
{
  LogRunnable::create();

  QThreadPool::globalInstance()->start(LogRunnable::getInstance());

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
  QThreadPool::globalInstance()->waitForDone();
  LogRunnable::destroy();
  qApp->quit();
}

