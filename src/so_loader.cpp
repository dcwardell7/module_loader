#include "./so_loader.hpp"

#include <dlfcn.h>
#include <stdexcept>

namespace sil {

SoLoader::
SoLoader(int f)
  : flags(f),
    modulesByName()
{
  if(!(flags & RTLD_NOW) && !(flags & RTLD_LAZY))
  {
    flags |= RTLD_NOW;
  }
  dlerror();
}

SoLoader::
~SoLoader()
{
  for(auto& kv : modulesByName)
  {
    auto entry = kv.second;
    close(entry.getHandle());
  }
}

auto SoLoader::
getFunc(const std::string& libName, const std::string& funcName) -> void*
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

auto SoLoader::
open(const std::string& libName) -> void*
{
  auto handle = dlopen(libName.c_str(), flags);
  assertDlError();

  return handle;
}

auto SoLoader::
getFunc(void* handle, const std::string& funcName) -> void*
{
  auto result = dlsym(handle, funcName.c_str());
  assertDlError();

  return result;
}

auto SoLoader::
close(void* handle) -> void
{
  dlclose(handle);
  assertDlError();
}

auto SoLoader::
assertDlError() -> void
{
  char* error;
  if((error = dlerror()) != nullptr)
  {
    std::string msg(error);
    throw std::runtime_error(msg);
  }
}

}
