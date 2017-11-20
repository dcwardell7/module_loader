#include "./module_entry.hpp"

namespace sil {

ModuleEntry::
ModuleEntry()
  : libName(),
    libHandle(0),
    funcHandles()
{}

ModuleEntry::
ModuleEntry(const std::string& name, void* handle)
  : libName(name),
    libHandle(handle),
    funcHandles()
{}

ModuleEntry::
~ModuleEntry()
{}

auto ModuleEntry::
getName() const -> std::string
{
  return libName;
}

auto ModuleEntry::
getHandle() const -> void*
{
  return libHandle;
}

auto ModuleEntry::
getFunc(const std::string& funcName) const -> void*
{
  auto entry = funcHandles.find(funcName);
  if(entry == funcHandles.end()) return nullptr;

  return entry->second;
}

auto ModuleEntry::
setFunc(const std::string& funcName, void* handle) -> void
{
  funcHandles[funcName] = handle;
}

auto ModuleEntry::
hasFunc(const std::string& funcName) const -> bool
{
  auto entry = funcHandles.find(funcName);
  return entry != funcHandles.end();
}

}
