#pragma once

#include "api.hpp"

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

	// ASSET MANAGER
	// Asset manager holds reponsibility of locating, indexing and veryfying assets
	// during runtime of the engine by creating specialized resource locator as per
	// its location in physical disk

	class AssetManager {
	private:
		static File::path _config;
		static std::unordered_map<enum AssetType, std::vector<File::path>> _folders;
		static std::unordered_map<File::path, Shared<void>> _laoded;
	public:
		
		// load and return the specified asset if not already loaded
		static Optional<Shared<void>> load_asset(File::path path);
		static Optional<Shared<void>> load_asset(enum AssetType t, String name);

		// retrive the specified asset if already loaded, doesnt load
		static Optional<Shared<void>> find_asset(File::path path);
		static Optional<Shared<void>> find_asset(enum AssetType t, String name);
		
		// remove cached element for specified path/file name from laoded
		static void remove_asset(File::path path);
		static void remove_asset(enum AssetType t, String name);

		// register specific path as specified asset type (for convieneince)
		static void register_asset(File::path path, enum AssetType t);
		static void register_folder(File::path path, enum AssetType t);

		// clear cache (only the _laoded counts as cache)
		static void clear();

		// configure Asset manager with base directory path
		static void configure_base(File::path base);
		static void configure_load();
		static void configure_save();
	};

	// ASSET CONFIGURATION FILE NAME
	#define ASSET_CONFIGURATION_FILE_NAME "assets.config"

	// ASSET RELATED RUNTIME ERRORS/EXCEPTIONS

	// asset wasnt fount at given locaton
	class AssetNotFoundError : public RuntimeError {
	private:
		String _message;
	public:
		AssetNotFoundError(File::path path);
		AssetNotFoundError(std::vector<File::path> paths);
		AssetNotFoundError(enum AssetType t, String path);
	public:
		const char* what() const noexcept override {
			return _message.c_str();
		}
	};

	// asset wasnt properly loaded due to some reason
	class AssetNotLoadedError :public RuntimeError {
	private:
		String _message;
	public:
		AssetNotLoadedError(String path, String reason);
		AssetNotLoadedError(std::vector<String> paths, String reason);
		AssetNotLoadedError(enum AssetType t, String path, String reason);
	public:
		const char* what() const noexcept override {
			return _message.c_str();
		}
	};
}