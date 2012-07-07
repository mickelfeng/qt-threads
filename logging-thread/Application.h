#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <vector>
#include <memory>
#include "SpamRunnable.h"

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
    std::vector<SpamRunnable*> m_threads;
};

#endif // APPLICATION_H

