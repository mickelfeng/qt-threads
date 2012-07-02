#include "StringSupplierRunner.h"
#include <iostream>
#include <unistd.h>

StringSupplierRunner::StringSupplierRunner(StringSupplier* supplier, 
  const std::string& str) 
  : m_str(str)
  , m_supplier(supplier)
{
}

void StringSupplierRunner::run()
{
  m_supplier->push(new std::string(m_str));
  std::cout << "PUSH " << m_str << std::endl;
  sleep(rand() % MAX_DURATION + 1);
}
