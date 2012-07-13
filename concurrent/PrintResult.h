#ifndef PRINTRESULT_H
#define PRINTRESULT_H

#include <QFutureWatcher>

class PrintResult : public QFutureWatcher<int>
{
  Q_OBJECT;

  public:
    PrintResult(QObject* parent = 0);

  public slots:
    void report();
};

#endif // PRINTRESULT_H

