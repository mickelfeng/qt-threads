#include "Processor.h"

Processor::Processor(QObject* parent) : QObject(parent)
{
}

int Processor::process(int* start, int n) const
{
  int sum = 0;
  for (int i = 0; i < n; ++i)
  {
    sum += start[i];
  }

  return sum;
}
