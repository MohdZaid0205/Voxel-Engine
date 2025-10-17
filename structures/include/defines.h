#ifndef STRUCTURES_DEFINES_H
#define STRUCTURES_DEFINES_H

#pragma region standardTemplates
	#define TEMPLATED_T template<typename T>
#pragma endregion

#pragma region standardExceptions
	#define MAV_EXCEPTION Structures::MemoryAccessViolation("Dealing with NULL pointer Perhaps.")
	#define ENF_EXCEPTION Structures::ElementNotFound("Cannot remove element from empty STRUCTURE.")
	#define IOR_EXCEPTION Structures::IndexOutOfRange("Cannot find specifed `_index` in STRUCTURE.")
#pragma endregion

#pragma region standardUtility
	#define INCREMENT(x) x++
	#define DECREMENT(x) x--
	#define PTR_NULLI(x) x = nullptr
	#define PTR_ALLOC(x, y) x = new y
	#define PTR_EQUAL(x, y) x = y
	#define PTR_DELOC(x) delete x
#pragma endregion

#pragma region standardQuality
	#define AND ;
	#define EXIT return
#pragma endregion

#pragma region definedConsts
	#define ZERO_32 0
	#define ZERO_64 0LL

#ifdef STRUCTURE_ARCH_x64
	#define ZERO_ ZERO_64
#else
	#define ZERO_ ZERO_32
#endif

#pragma endregion

#endif