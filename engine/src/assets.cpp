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

// ALLOCATE STATIC DATA
Engine::File::path Engine::AssetManager::_config;

// ALLOCATE STATIC DATA
std::unordered_map<enum Engine::AssetType, std::vector<Engine::File::path>> Engine::AssetManager::_folders 
	= std::unordered_map<enum Engine::AssetType, std::vector<Engine::File::path>>();

// ALLOCATE STATIC DATA
std::unordered_map<enum Engine::AssetType, Engine::Unique<Engine::IAssetLoader>> Engine::AssetManager::_loaders
= std::unordered_map<enum Engine::AssetType, Engine::Unique<Engine::IAssetLoader>>();

// ALLOCATE STATIC DATA
std::unordered_map<Engine::File::path, Engine::Shared<void>> _laoded
	= std::unordered_map<Engine::File::path, Engine::Shared<void>>();

// CLASSES IMPLEMENTATION

void Engine::AssetManager::configure_base(File::path base) {
	AssetManager::_config = base/ASSET_CONFIGURATION_FILE_NAME;
	
	// use predefined configuration file name to load config
	if (!File::exists(AssetManager::_config)) {

		// setup folder logic
		auto setupFolder = [base](enum AssetType t) {
			try {
				File::path folder = base/(assetTypeAsString(t) + "s");
				if (!File::exists(folder)) {
					File::create_directory(folder);
				}
				AssetManager::_folders[t].push_back(folder);
				return Attempt::Status::PASS;
			}
			catch (RuntimeError& err) {
				return Attempt::Status::FAIL;
			}

			return Attempt::Status::WARN;
		};

		// attemp and logs
		auto attemptSetupFolder = [base, setupFolder](enum AssetType t) {
			Attempt::to<HIG>([base, setupFolder, t]() { return setupFolder(t); })
				.does("Register Asset Folder:"_D		+ assetTypeAsString(t) + "s")
				.fail("Failed to register Folder:"_D	+ assetTypeAsString(t) + "s")
				.pass("Registered Folder:"_D			+ assetTypeAsString(t) + "s")
				.warn("Unexpected behaviour Folder:"_D	+ assetTypeAsString(t) + "s")
			;
		};

		attemptSetupFolder(Config);
		attemptSetupFolder(Font);
		attemptSetupFolder(Icon);
		attemptSetupFolder(Script);
		attemptSetupFolder(Shader);
		attemptSetupFolder(Sound);
		attemptSetupFolder(Image);
		attemptSetupFolder(Texture);
		attemptSetupFolder(Voxel);

		// TODO: copy presets to the defined folders
		// ...

		AssetManager::configure_save();
	}
	else {
		AssetManager::configure_load();
	}
}

void Engine::AssetManager::configure_save() {

	// Save Folder informations
	auto writeHeading = [](FileOutput& file, String heading) {
		if (file.is_open()) {
			file << heading << '\n';
		}
	};

	// Save data to configuration
	auto writeValue = [](FileOutput& file, enum AssetType t, File::path path) {
		if (file.is_open()) {
			file << assetTypeAsString(t) << " : " << path;
		}
	};

	auto attemptWritingConfig = [writeHeading, writeValue]() {
		try {
			FileOutput config_file = FileOutput(_config, std::ios::out | std::ios::trunc);

			// iterate over folder types and save the required information
			writeHeading(config_file, "!FOLDERS");
			for (auto& val : _folders) {
				for (auto& path : val.second) {
					writeValue(config_file, val.first, path);
				}
			}

			// TODO: maybe do somethign about the files
			// ...

			// Write Ending heading
			writeHeading(config_file, "!END");

			return Attempt::Status::PASS;
		}
		catch (RuntimeError& err) {
			return Attempt::Status::FAIL;
		}

		return Attempt::Status::WARN;
	};

	Attempt::to<HIG>(attemptWritingConfig)
		.does("Write"_D, ASSET_CONFIGURATION_FILE_NAME, "at:"_D, _config)
		.pass("File Written:"_D, _config, "Configuration stored!"_D)
		.fail("File Write Failed for:"_D, _config, "store failed!"_D)
		.warn("File Write Resulted in unexpected behaviour:", _config)
	;
}

void Engine::AssetManager::configure_load() {
	
	// Read Heading
	auto loadHeading = [](FileInput& file) {
		String heading;
		if (file.is_open()) {
			file >> heading;
		}
		return heading;
	};

	// Read Contents
	auto loadFolderConfig = [](FileInput& file) {
		String type;
		char seperate;
		File::path path;

		if (file.is_open()) {
			std::streampos p = file.tellg();
			file >> type;
			if (type[0] == '!') {
				file.seekg(p);
				return false;
			}
			else
				file >> seperate >> path;
		}
		_folders[assetStringAsType(type)].push_back(path);
		return true;
	};

	// .. (other Config loader)

	// .. (load reqiored config)
	bool loading = true;
	FileInput src = FileInput(_config);
	while (loading) {
		String heading = loadHeading(src);
		if (heading == "!END") {
			loading = false;
		} else if (heading == "!FOLDERS") {
			while (loadFolderConfig(src)) {}
		}
		else {
			// do nothing
		}
	}
}

Engine::Optional<Engine::Shared<void>> Engine::AssetManager::load_asset(File::path path){
	Shared<void> data;
	bool done = false;

	for (auto& ldr : _loaders) {
		if (ldr.second->works(path)) {
			if (done)
				throw AssetNotLoadedError(path, "Multiple loaders work with specified path, cannot choose one!");

			data = ldr.second->load(path);
			done = true;
		}
	}
	return data;
}
