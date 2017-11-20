#include "sil/module_loader.hpp"

#include "./so_loader.hpp"

namespace sil {

class ModuleLoader::Impl
{
public:
  Impl(int flags)
    : soLoader(std::make_unique<SoLoader>(flags))
  {}

  virtual ~Impl()
  {}

  void* getFuncPtr(const std::string& libName, const std::string& funcName)
  {
    return soLoader->getFunc(libName, funcName);
  }
private:
  std::unique_ptr<SoLoader> soLoader;
};

ModuleLoader::
ModuleLoader(int flags)
  : impl(std::make_unique<Impl>(flags))
{}

ModuleLoader::
~ModuleLoader()
{}

auto ModuleLoader::
getFuncPtr(const std::string& libName, const std::string& funcName) -> void*
{
  return impl->getFuncPtr(libName, funcName);
}

}
