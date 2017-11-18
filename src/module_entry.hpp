#ifndef SIL_MODULE_ENTRY_HPP
#define SIL_MODULE_ENTRY_HPP

#include <map>
#include <string>

namespace sil {

struct ModuleEntry
{
public:
	ModuleEntry();
	ModuleEntry(const std::string& libName, void* handle);
	virtual ~ModuleEntry();
	std::string getName() const;
	void* getHandle() const;
	void setFunc(const std::string& funcName, void* handle);
	void* getFunc(const std::string& funcName) const;
	bool hasFunc(const std::string& funcName) const;

private:
	std::string libName;
	void* libHandle;
	std::map<std::string, void*> funcHandles;
};

}

#endif
