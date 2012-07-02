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

    // Display the window and start the worker threads
    window.show();
    window.start();

    // Create a timer to call lock() on thread A
    QTimer timerA;
    timerA.setInterval(5000);
    timerA.setSingleShot(true);

    // Create a timer to call lock() on thread B
    QTimer timerB;
    timerB.setInterval(3000);
    timerB.setSingleShot(true);

    // Connect the timers to the main window
    QObject::connect(&timerA, SIGNAL(timeout()), &window, SLOT(lockA()));
    QObject::connect(&timerB, SIGNAL(timeout()), &window, SLOT(lockB()));

    // Start the timers
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
