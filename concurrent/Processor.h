#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <QObject>

/**
 *
 */
class Processor : public QObject
{
  Q_OBJECT;

  public:
    Processor(QObject* parent = 0);
    int process(int* start, int n) const;
};

#endif // PROCESSOR_H

