#include "Processor.h"

Processor::Processor(QObject* parent) : QObject(parent)
{
}

int Processor::process(const std::vector<int>& data) const
{
  int sum = 0;
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    sum += *it;
  }

  return sum;
}
