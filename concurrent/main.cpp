#include <stdexcept>
#include <iostream>
#include "Application.h"

int main(int argc, char** argv)
{
  try
  {
    Application app(argc, argv);
    return app.exec();
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
