#include "./class_greeter.hpp"

namespace sil { namespace test {

ClassGreeter::
ClassGreeter()
{}

ClassGreeter::
~ClassGreeter()
{}

auto ClassGreeter::
greet() const -> std::string
{
	return "Hello, Class!";
}

} }

extern "C" {

sil::test::Greeter* create()
{
	return new sil::test::ClassGreeter();
}

void destroy(sil::test::Greeter* instance)
{
	delete instance;
}

}
