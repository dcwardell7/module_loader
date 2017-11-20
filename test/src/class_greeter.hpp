#ifndef SIL_TEST_CLASS_GREETER_HPP
#define SIL_TEST_CLASS_GREETER_HPP

#include <string>
#include "greeter.hpp"

namespace sil { namespace test {

class ClassGreeter : public Greeter
{
public:
  ClassGreeter();
  virtual ~ClassGreeter();
  std::string greet() const;
private:
};

} }

#endif
