#pragma once

#include "api.hpp"
#include "exceptions.hpp"

namespace Engine {

	enum AssetType {
		Unknown,		// AssetType UNKNOWN (uncategorized)
		Config,			// AssetType CONFIG (special configurations)
		Font,			// AssetType FONT (.ttf or any other supported font format)
		Icon,			// AssetType ICON (.svg, .png, .jpg)
		Script,			// AssetType SCRIPT (specialized scripts for components)
		Shader,			// AssetType SHADER (fragment/vertex/compute)
		Sound,			// AssetType SOUND (.mp4, or any other playable format)
		Image,			// AssetType IMAGE (.png, .jpg)
		Texture,		// AssetType TEXTURE (.png, jpg)
		Voxel,			// AsserType VOXEL (.vxl specialized representaion of cube)
	};

	String assetTypeAsString(enum AssetType t);
	enum AssetType assetStringAsType(String s);

	// ASSET REGISTERY -----------------------------------------------------------------+
	// asset registery is responosible for holding shared reference of registered data	|
	// these data are often accessed everytime and cannot be loaded multiple times in	|
	// order to save performance issues, this is solely for maintaining lifecycle of	|
	// assets at runtime																|
	// ---------------------------------------------------------------------------------+
	
	class IAssetRegistery {
	public:
		virtual ~IAssetRegistery() = default;
		virtual void clear() = 0;
	};

	template<typename T>
	class AssetRegistry:public IAssetRegistery {
	private:
		idxx				__loads_identifier__ = 0;
		std::vector<idxx>	__empty_identifier__;
	private:
		std::unordered_map<idxx, Shared<T>>	 _loaded;
		std::unordered_map<File::path, idxx> _locate;
	public:
		Expected<idxx> store(File::path path, Shared<T> data);
		Expected<void> remove(File::path path);
		Expected<void> remove(idxx identifier);
	public:
		Expected<Shared<T>> load(File::path path);
		Expected<Shared<T>> load(idxx identifier);
	public:
		void clear() override;
	};

	// ASSET REGISTERATION PROBLEMS
	Attempt::Status AssetRegisterationFailed(String message);
	Attempt::Status AssetRegisterationFailed(File::path path, String due);

	// ASSET REMOVAL PROBLEMS
	Attempt::Status AssetRemovalFailed(String message);
	Attempt::Status AssetRemovalFailed(File::path path, String due);
	Attempt::Status AssetRemovalFailed(idxx identifier, String due);

	// ASSET MANAGER and ASSET LOLADER INTERFACE ---------------------------------------+
	// Asset manager holds reponsibility of locating, indexing and veryfying assets		|
	// during runtime of the engine by creating specialized resource locator as per		|
	// its location in physical disk													|
	// ---------------------------------------------------------------------------------+

	class AssetManager {
	private:
		std::unordered_map<std::type_index, std::unique_ptr<IAssetRegistery>> _registries;
	private:
		template<typename T> AssetRegistry<T>* getRegistry();
	public:
		template<typename T> Expected<idxx> store(File::path path, Shared<T> data);
		template<typename T> Expected<void> remove(File::path path);
		template<typename T> Expected<void> remove(idxx identifier);
	public:
		template<typename T> Expected<Shared<T>> load(File::path path);
		template<typename T> Expected<Shared<T>> load(idxx identifier);
	public:
		void clearAll();
	};
	
	// ASSET NOT FOUND ERROR
	Attempt::Status AssetNotFoundError(String message);
	Attempt::Status AssetNotFoundError(File::path path);
	Attempt::Status AssetNotFoundError(std::vector<File::path> paths);

	// ASSET NOT LOADED ERROR
	Attempt::Status AssetNotLoadedError(String message);
	Attempt::Status AssetNotLoadedError(File::path path);
	Attempt::Status AssetNotLoadedError(std::vector<File::path> paths);
}

#include "assets.inl"
