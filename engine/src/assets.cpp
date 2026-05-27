#include "assets.hpp"

// dependencies
#include "logging.hpp"

// FUNCTIONS IMPLEMENTATIONS

Engine::String Engine::assetTypeAsString(enum AssetType t) {
	switch (t)
	{
	case Engine::Unknown:
		return "Unknown";
	case Engine::Config:
		return "Config";
	case Engine::Font:
		return "Font";
	case Engine::Icon:
		return "Icon";
	case Engine::Script:
		return "Script";
	case Engine::Shader:
		return "Shader";
	case Engine::Sound:
		return "Sound";
	case Engine::Image:
		return "Image";
	case Engine::Texture:
		return "Texture";
	case Engine::Voxel:
		return "Voxel";
	default:
		return "Unknown";
	}
}

#define COMPARE_AND_RETURN(w) if (s.compare(#w)) return w;

enum Engine::AssetType Engine::assetStringAsType(String s) {
	COMPARE_AND_RETURN(Config);
	COMPARE_AND_RETURN(Font);
	COMPARE_AND_RETURN(Icon);
	COMPARE_AND_RETURN(Script);
	COMPARE_AND_RETURN(Shader);
	COMPARE_AND_RETURN(Sound);
	COMPARE_AND_RETURN(Image);
	COMPARE_AND_RETURN(Texture);
	COMPARE_AND_RETURN(Voxel);
	COMPARE_AND_RETURN(Unknown);
	return Unknown;
}

// EXCEPTIONS/ERRORS/WARNINGS

Engine::Attempt::Status Engine::AssetNotFoundError(String message){
	return Attempt::Status{
		Attempt::Status::Error,
		"AssetNotFoundError", message
	};
}

Engine::Attempt::Status Engine::AssetNotFoundError(File::path path){
	return Engine::AssetNotFoundError(
		(String)"Could not find specified Asset at path:" + path.string()
	);
}

Engine::Attempt::Status Engine::AssetNotFoundError(std::vector<File::path> paths){
	String all_paths = "";
	for (auto& path : paths) {
		all_paths += path.string();
	}
	return Engine::AssetNotFoundError(
		(String)"Could not find specified Asset at:" + all_paths
	);
}

Engine::Attempt::Status Engine::AssetNotLoadedError(String message){
	return Attempt::Status{
		Attempt::Status::Error,
		"AssetNotLoadedError", message
	};
}

Engine::Attempt::Status Engine::AssetNotLoadedError(File::path path) {
	return Engine::AssetNotLoadedError(
		(String)"Could not find specified Asset at path:" + path.string()
	);
}

Engine::Attempt::Status Engine::AssetNotLoadedError(std::vector<File::path> paths) {
	String all_paths = "";
	for (auto& path : paths) {
		all_paths += path.string();
	}
	return Engine::AssetNotLoadedError(
		(String)"Could not find specified Asset at:" + all_paths
	);
}
