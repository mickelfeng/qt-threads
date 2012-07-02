#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <vector>
#include <memory>
#include "Thread.h"

/**
 *
 */
class Application : public QApplication
{
  Q_OBJECT;

  public:
    Application(int argc, char** argv);

  public slots:
    void timeout();

  private:
    std::vector<std::unique_ptr<Thread>> m_threads;
};

#endif // APPLICATION_H

