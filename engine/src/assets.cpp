#include "assets.hpp"

// dependencies
#include "logging.hpp"

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

// ALLOCATE STATIC DATA
Engine::File::path Engine::AssetManager::_config;

// ALLOCATE STATIC DATA
std::unordered_map<enum Engine::AssetType, std::vector<Engine::File::path>> Engine::AssetManager::_folders 
	= std::unordered_map<enum Engine::AssetType, std::vector<Engine::File::path>>();

// ALLOCATE STATIC DATA
std::unordered_map<Engine::File::path, Engine::Shared<void>> _laoded
	= std::unordered_map<Engine::File::path, Engine::Shared<void>>();


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
		auto attemptSetupFolder = [base, setupFolder](enum AssetType) {
			Attempt::to<HIG>([base, setupFolder]() { return setupFolder(Font); })
				.does("Register Asset Folder:"_D + assetTypeAsString(Font) + "s")
				.fail("Failed to register Folder:"_D + assetTypeAsString(Font) + "s")
				.pass("Registered Folder:"_D + assetTypeAsString(Font) + "s")
				.warn("Unexpected behaviour Folder:"_D + assetTypeAsString(Font) + "s")
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
	auto writeHeading = [](FileOutput& to, String heading) {
		if (to.is_open()) {
			to << heading << '\n';
		}
	};

	// Save data to configuration
	auto writeValue = [](FileOutput& to, enum AssetType t, File::path path) {
		if (to.is_open()) {
			to << assetTypeAsString(t) << " : " << path;
		}
	};

	auto attemptWritingConfig = [writeHeading, writeValue]() {
		try {
			FileOutput config_file = FileOutput(_config, std::ios::out | std::ios::trunc);

			// iterate over folder types and save the required information
			writeHeading(config_file, "FOLDERS");
			for (auto& val : _folders) {
				for (auto& path : val.second) {
					writeValue(config_file, val.first, path);
				}
			}

			// TODO: maybe do somethign about the files
			// ...

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