#ifndef STRUCTURES_DEFINES_H
#define STRUCTURES_DEFINES_H

#pragma region standardTemplates
	#define TEMPLATED_T template<typename T>
#pragma endregion

#pragma region standardExceptions
	#define ENF_EXCEPTION Structures::ElementNotFound("Cannot remove element from empty STRUCTURE.")
	#define IOR_EXCEPTION Structures::IndexOutOfRange("Cannot find specifed `_index` in STRUCTURE.")
#pragma endregion

#pragma region standardUtility
	#define INCREMENT(x) (x)++
	#define DECREMENT(x) (x)--
	#define PTR_NULLI(x) (x) = nullptr
	#define PTR_ALLOC(x, y) (x) = new (y)
	#define PTR_DELOC(x) delete (x)
#pragma endregion

#pragma region standardQuality
	#define AND ;
	#define EXIT return
#pragma endregion

#endif