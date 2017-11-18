#include "sil/module_loader.hpp"
#include "greeter.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	auto funcLib = "libgreeter.so";
	auto classLib = "libclass_greeter.so";
	auto loader = std::make_shared<sil::ModuleLoader>();
	auto greet = loader->getFunc<void()>(funcLib, "sayHello");
	auto greeter = loader->getClass<sil::test::Greeter>(classLib);

	greet();
	std::cout << greeter->greet() << std::endl;
}
