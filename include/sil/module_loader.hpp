#ifndef SIL_MODULE_LOADER_HPP
#define SIL_MODULE_LOADER_HPP

#include <functional>
#include <memory>
#include <string>

namespace sil {

class ModuleLoader
{
public:
	typedef std::shared_ptr<ModuleLoader> SPtr;

public:
	ModuleLoader(int flags = 0);
	virtual ~ModuleLoader();
	template<typename Signature> std::function<Signature> getFunc(const std::string& libName, const std::string& funcName);
	template<typename T> std::shared_ptr<T> getClass(const std::string& libName, const std::string& createFunc, const std::string& destroyFunc);
	template<typename T> std::shared_ptr<T> getClass(const std::string& libName);

private:
	class Impl;
	std::unique_ptr<Impl> impl;

private:
	void* getFuncPtr(const std::string& libName, const std::string& funcName);
};

template<typename Signature>
auto ModuleLoader::
getFunc(const std::string& libName, const std::string& funcName) -> std::function<Signature>
{
	Signature* handle;
	*(void**) (&handle) = getFuncPtr(libName, funcName);
	return std::function<Signature>(handle);
}

template<typename T>
auto ModuleLoader::
getClass(const std::string& libName, const std::string& createName, const std::string& destroyName) -> std::shared_ptr<T>
{
	auto createFunc = getFunc<T*()>(libName, createName);
	auto destroyFunc = getFunc<void(T*)>(libName, destroyName);
	auto instance = createFunc();

	return std::shared_ptr<T>(instance, [destroyFunc](T* instance){
		destroyFunc(instance);
	});
}

template<typename T>
auto ModuleLoader::
getClass(const std::string& libName) -> std::shared_ptr<T>
{
	return getClass<T>(libName, "create", "destroy");
}

}

#endif
