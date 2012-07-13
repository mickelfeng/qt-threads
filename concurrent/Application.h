#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

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
};

#endif // APPLICATION_H

