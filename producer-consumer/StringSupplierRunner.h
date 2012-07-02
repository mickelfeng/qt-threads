#ifndef STRINGSUPPLIERRUNNER_H
#define STRINGSUPPLIERRUNNER_H

#include "Thread.h"
#include "Supplier.h"
#include <string>
#include <memory>

typedef Supplier<std::string> StringSupplier;

class StringSupplierRunner : public ThreadRunner
{
  public:
    StringSupplierRunner(StringSupplier* supplier, const std::string& str);

    virtual void run();

  private:
    std::string m_str;
    std::unique_ptr<StringSupplier> m_supplier;

    static const int MAX_DURATION = 3;
};

#endif // STRINGSUPPLIERRUNNER_H

