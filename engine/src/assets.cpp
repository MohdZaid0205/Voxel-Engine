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

Engine::Attempt::Status Engine::AssetRegisterationFailed(String message) {
    return Attempt::makeRecoverableError("AssetRegistrationFailed", message);
}

Engine::Attempt::Status Engine::AssetRegisterationFailed(File::path path, String due) {
    return Attempt::makeRecoverableError("AssetRegistrationFailed",
        "Failed to register '" + path.string() + "': " + due);
}

Engine::Attempt::Status Engine::AssetRemovalFailed(String message) {
    return Attempt::makeRecoverableError("AssetRemovalFailed", message);
}

Engine::Attempt::Status Engine::AssetRemovalFailed(File::path path, String due) {
    return Attempt::makeRecoverableError("AssetRemovalFailed",
        "Failed to remove '" + path.string() + "': " + due);
}

Engine::Attempt::Status Engine::AssetRemovalFailed(idxx identifier, String due) {
    return Attempt::makeRecoverableError("AssetRemovalFailed",
        "Failed to remove ID [" + std::to_string(identifier) + "]: " + due);
}

Engine::Attempt::Status Engine::AssetNotFoundError(String message) {
    return Attempt::makeRecoverableError("AssetNotFoundError", message);
}

Engine::Attempt::Status Engine::AssetNotFoundError(File::path path) {
    return Attempt::makeRecoverableError("AssetNotFoundError",
        "Could not find asset at path: " + path.string());
}

Engine::Attempt::Status Engine::AssetNotFoundError(std::vector<File::path> paths) {
    std::ostringstream oss;
    oss << "Could not find assets at paths: ";
    for (size_t i = 0; i < paths.size(); ++i) {
        oss << paths[i].string() << (i < paths.size() - 1 ? ", " : "");
    }
    return Attempt::makeRecoverableError("AssetNotFoundError", oss.str());
}

Engine::Attempt::Status Engine::AssetNotLoadedError(String message) {
    return Attempt::makeRecoverableError("AssetNotLoadedError", message);
}

Engine::Attempt::Status Engine::AssetNotLoadedError(File::path path) {
    return Attempt::makeRecoverableError("AssetNotLoadedError",
        "Asset not loaded at path: " + path.string());
}

Engine::Attempt::Status Engine::AssetNotLoadedError(std::vector<File::path> paths) {
    std::ostringstream oss;
    oss << "Assets not loaded at paths: ";
    for (size_t i = 0; i < paths.size(); ++i) {
        oss << paths[i].string() << (i < paths.size() - 1 ? ", " : "");
    }
    return Attempt::makeRecoverableError("AssetNotLoadedError", oss.str());
}