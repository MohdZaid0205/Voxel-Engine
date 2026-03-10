#pragma once

#include "api.hpp"
#include "logging.hpp"

namespace Engine {

	// Approach
	// any voxel is defined solely by voxel idxx, idxx represent position within VoxelContainer
	// this is to imporve cache locality. this is my attempt at creating MultiList specifically
	// for purpose of Voxel representation
	
	struct Voxel {
		idxx identifier;
		u32* shader;
		u32* texture;
	};

	class VoxelContainer {
	private:
		static std::vector<u32> shader;
		static std::vector<u32> texture;
		static idxx size;
	public:
		static Voxel get(idxx id);
		static Voxel add(u32 shader_id, u32 texture_id);
	};

};