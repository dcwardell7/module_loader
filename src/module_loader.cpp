#include "sil/module_loader.hpp"

#include <dlfcn.h>
#include <map>
#include <stdexcept>

#include "./module_entry.hpp"

namespace sil {

class ModuleLoader::Impl
{
public:
  Impl(int f)
    : flags(f),
      modulesByName()
  {
    if(!(flags & RTLD_NOW) && !(flags & RTLD_LAZY))
    {
      flags |= RTLD_NOW;
    }
    dlerror();
  }

  virtual ~Impl()
  {
    for(auto& kv : modulesByName)
    {
      auto entry = kv.second;
      close(entry.getHandle());
    }
  }

  void* getFuncPtr(const std::string& libName, const std::string& funcName)
  {
    auto kv = modulesByName.find(libName);
    ModuleEntry entry;

    // Lazy load new libraries
    if(kv == modulesByName.end()) {
      auto libHandle = open(libName);
      entry = ModuleEntry(libName, libHandle);
      modulesByName[libName] = entry;
    } else {
      entry = kv->second;
    }

    // Lazy load new functions
    if(!entry.hasFunc(funcName)) {
      auto libHandle = entry.getHandle();
      auto funcHandle = getFunc(libHandle, funcName);
      entry.setFunc(funcName, funcHandle);
    }

    return entry.getFunc(funcName);
  }

private:
  typedef std::map<std::string, ModuleEntry> ModuleMap;

private:
  int flags;
  ModuleMap modulesByName;

private:
  void* open(const std::string& libName)
  {
    auto handle = dlopen(libName.c_str(), flags);
    assertDlError();

    return handle;
  }

  void* getFunc(void* handle, const std::string& funcName)
  {
    auto result = dlsym(handle, funcName.c_str());
    assertDlError();

    return result;
  }

  void close(void* handle)
  {
    dlclose(handle);
    assertDlError();
  }

  void assertDlError()
  {
    char* error;
    if((error = dlerror()) != nullptr)
    {
      std::string msg(error);
      throw std::runtime_error(msg);
    }
  }
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
