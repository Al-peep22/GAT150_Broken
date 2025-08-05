#pragma once
#include <string>
#include <map>
#include "Core/StringHelper.h"
#include "Resource.h"
#include <memory>
#include <iostream>

namespace viper {
	class ResourceManager {
	public:
		template <typename T, typename ... TArgs>
		res_t<T>Get(const std::string& name, TArgs&& ... args);



	private:
		std::map<std::string, res_t<Resource>> resources;
	};

	template <typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& name, TArgs&& ... args)
	{
		std::string key = tolower(name);

		auto iter = resources.find(key);
		if (iter != resources.end()) {
			auto base = iter->second;
			auto derived = std::dynamic_pointer_cast<T>(base);
			if (derived == nullptr) {
				std::cerr << "Resource type mismatch: " << key << std::endl;
				return res_t<T>();
			}
			return derived;
		}

		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(key, std::forward<TArgs>(args)...) == false) {
			std::cerr << "Failed to load resource: " << key << std::endl;
			return res_t<T>();
		}

		resources[key] = resource;
		return resource;
	}
}