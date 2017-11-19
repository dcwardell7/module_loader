#ifndef SIL_SO_LOADER_HPP
#define SIL_SO_LOADER_HPP

#include <map>
#include <memory>
#include <string>

#include "./module_entry.hpp"

namespace sil {

class SoLoader
{
public:
	SoLoader(int flags);
	virtual ~SoLoader();
	void* getFunc(const std::string& libName, const std::string& funcName);

private:
	typedef std::map<std::string, ModuleEntry> ModuleMap;

private:
	int flags;
	ModuleMap modulesByName;

private:
	void* open(const std::string& libName);
	void* getFunc(void* handle, const std::string& funcName);
	void close(void* handle);
	void assertDlError();
};

}

#endif
