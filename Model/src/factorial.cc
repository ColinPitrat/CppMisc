#include <stdexcept>
#include <sstream>

uint64_t factorial(uint64_t n)
{
  uint64_t c = n;
  uint64_t r = 1;
  while(c > 0) {
    if((UINT64_MAX / c) < r) {
      std::ostringstream msg;
      msg << "Factorial of " << n << " is too big for a uint64_t.";
      std::out_of_range e(msg.str());
      throw e;
    }
    r *= c--;
  }
  return r;
}

