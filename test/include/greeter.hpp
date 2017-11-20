#ifndef SIL_TEST_GREETER_HPP
#define SIL_TEST_GREETER_HPP

#include <string>

namespace sil { namespace test {

class Greeter
{
public:
  virtual ~Greeter(){};
  virtual std::string greet() const = 0;
};

} }

#endif
