#include "PrintResult.h"
#include <iostream>

PrintResult::PrintResult(QObject* parent) 
: QFutureWatcher<int>(parent)
{
  connect(this, SIGNAL(finished()), this, SLOT(report()));
}

void PrintResult::report()
{
  emit sum(result());
}

