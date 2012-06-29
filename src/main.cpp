#include <stdexcept>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include "MainWindow.h"

int main(int argc, char** argv)
{
  try
  {
    QApplication app(argc, argv);
    MainWindow window;

    window.show();
    window.start();

    QTimer timerA;
    timerA.setInterval(5000);
    timerA.setSingleShot(true);

    QTimer timerB;
    timerB.setInterval(5000);
    timerB.setSingleShot(true);

    QObject::connect(&timerA, SIGNAL(timeout()), &window, SLOT(lockA()));
    QObject::connect(&timerB, SIGNAL(timeout()), &window, SLOT(lockB()));

    timerA.start();
    timerB.start();

    app.exec();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Encountered unrecognized exception" << std::endl;
  }

  return 0;
}
