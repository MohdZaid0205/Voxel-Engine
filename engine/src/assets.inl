
#pragma region Engine::AssetRegistry Implementation

template<typename T>inline Engine::Expected<Engine::idxx>
Engine::AssetRegistry<T>::store(File::path path, Shared<T> data) {
	if (_locate.find(path) != _locate.end()) {
		return std::unexpected(Engine::AssetRegisterationFailed(path, "Asset path already registered."));
	}

	idxx identifier;
	if (!__empty_identifier__.empty()) {
		identifier = __empty_identifier__.back();
		__empty_identifier__.pop_back();
	}
	else {
		identifier = ++__loads_identifier__;
	}

	_loaded[identifier] = data;
	_locate[path] = identifier;

	return identifier;
}

template<typename T>inline Engine::Expected<void>
Engine::AssetRegistry<T>::remove(File::path path) {
	auto it = _locate.find(path);
	if (it == _locate.end()) {
		return std::unexpected(Engine::AssetRemovalFailed(path, "Path not found in registry."));
	}

	idxx identifier = it->second;
	_locate.erase(it);
	_loaded.erase(identifier);

	__empty_identifier__.push_back(identifier);

	return {};
}

template<typename T>inline Engine::Expected<void>
Engine::AssetRegistry<T>::remove(idxx identifier) {
	auto loaded_it = _loaded.find(identifier);
	if (loaded_it == _loaded.end()) {
		return std::unexpected(Engine::AssetRemovalFailed(identifier, "Identifier not found in registry."));
	}

	for (auto it = _locate.begin(); it != _locate.end(); ++it) {
		if (it->second == identifier) {
			_locate.erase(it);
			break;
		}
	}

	_loaded.erase(loaded_it);
	__empty_identifier__.push_back(identifier);

	return {};
}

template<typename T>inline Engine::Expected<Engine::Shared<T>>
Engine::AssetRegistry<T>::load(File::path path) {
	auto it = _locate.find(path);
	if (it == _locate.end()) {
		return std::unexpected(Engine::AssetNotFoundError(path));
	}

	return load(it->second);
}

template<typename T>inline Engine::Expected<Engine::Shared<T>>
Engine::AssetRegistry<T>::load(idxx identifier) {
	auto it = _loaded.find(identifier);
	if (it == _loaded.end()) {
		return std::unexpected(Engine::AssetNotLoadedError(Engine::String("Asset identifier exists but data is null/missing.")));
	}

	return it->second;
}

template<typename T>inline void
Engine::AssetRegistry<T>::clear() {
	_loaded.clear();
	_locate.clear();
	__empty_identifier__.clear();
	__loads_identifier__ = 0;
}

#pragma endregion

#pragma region Engine::AssetManager Implementation

template<typename T>inline Engine::AssetRegistry<T>*
Engine::AssetManager::getRegistry() {
	std::type_index typeIdx(typeid(T));
	auto it = _registries.find(typeIdx);
	if (it == _registries.end()) {
		auto newRegistry = std::make_unique<Engine::AssetRegistry<T>>();
		auto* ptr = newRegistry.get();
		_registries[typeIdx] = std::move(newRegistry);
		return ptr;
	}
	return static_cast<Engine::AssetRegistry<T>*>(it->second.get());
}

template<typename T>inline Engine::Expected<Engine::idxx>
Engine::AssetManager::store(File::path path, Shared<T> data) {
	return getRegistry<T>()->store(path, data);
}

template<typename T>inline Engine::Expected<void>
Engine::AssetManager::remove(File::path path) {
	return getRegistry<T>()->remove(path);
}

template<typename T>inline Engine::Expected<void>
Engine::AssetManager::remove(idxx identifier) {
	return getRegistry<T>()->remove(identifier);
}

template<typename T>inline Engine::Expected<Engine::Shared<T>>
Engine::AssetManager::load(File::path path) {
	return getRegistry<T>()->load(path);
}

template<typename T>inline Engine::Expected<Engine::Shared<T>>
Engine::AssetManager::load(idxx identifier) {
	return getRegistry<T>()->load(identifier);
}

inline void
Engine::AssetManager::clearAll() {
	for (auto& [type, registry] : _registries) {
		registry->clear();
	}
	_registries.clear();
}

#pragma endregion