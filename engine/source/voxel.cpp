#include "voxel.hpp"

std::vector<Engine::u32> Engine::VoxelContainer::shader  = std::vector<Engine::u32>();
std::vector<Engine::u32> Engine::VoxelContainer::texture = std::vector<Engine::u32>();
Engine::idxx Engine::VoxelContainer::size = 0;

struct Engine::Voxel Engine::VoxelContainer::get(idxx id){
	
	if (id > size)
		return { Engine::idxx_INVALID, nullptr, nullptr };

	return {
		.identifier = id,
		.shader		= &shader[id],
		.texture	= &texture[id]
	};
}

struct Engine::Voxel Engine::VoxelContainer::add(u32 shader_id, u32 texture_id) {
	try {
		shader.push_back(shader_id);
		texture.push_back(texture_id);
	}
	catch (std::runtime_error e) {
		return { Engine::idxx_INVALID, nullptr, nullptr };
	}

	return {
		.identifier = size++,
		.shader		= &shader[size],
		.texture	= &texture[size]
	};
}
