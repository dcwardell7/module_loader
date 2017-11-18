#include "./module_entry.hpp"

namespace sil {

ModuleEntry::
ModuleEntry()
{}

ModuleEntry::
ModuleEntry(const std::string& libName, void* handle)
  : libName(libName),
	libHandle(handle)
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
