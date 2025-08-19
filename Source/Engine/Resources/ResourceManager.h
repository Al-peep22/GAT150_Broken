#pragma once
#include <string>
#include <map>
#include "Core/StringHelper.h"
#include "Core/Singleton.h"
#include "Resource.h"
#include <memory>
#include <iostream>
#include "Core/Logger.h"

namespace viper {
	class ResourceManager : public Singleton<ResourceManager> {
	public:

		void Clear() { resources.clear(); }

		template <typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		inline res_t<T>Get(const std::string& name, Args&& ... args);
		
		template <typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		res_t<T>GetWithID(const std::string& id, const std::string& name, Args&& ... args);

		static ResourceManager& Instance() {
			static ResourceManager instance;
			return instance;
		}

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;


	private:
		std::map<std::string, res_t<Resource>> resources;
	};

	template <typename T, typename ... Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args) {
		return GetWithID<T>(name, name, std::forward<Args>(args)...);
	}

	template <typename T, typename ... Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args&& ... args)
	{
		std::string key = toLower(id);

		auto iter = resources.find(key);
		if (iter != resources.end()) {
			auto base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>(base);
			if (resource == nullptr) {
				Logger::Error("Resource type mismatch: {}", key);
				return res_t<T>();
			}
			return resource;
		}

		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<Args>(args)...) == false) {
			Logger::Error("Failed to load resource: {}", name);
			return res_t<T>();
		}

		resources[key] = resource;
		return resource;
	}

	inline ResourceManager& Resources() {
		return ResourceManager::Instance();
	}
}