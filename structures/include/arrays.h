#ifndef STRUCTURES_ARRAY_H
#define STRUCTURES_ARRAY_H

#include "exceptions.h"

namespace Structures {

	/*
	* This file contains implimentation for StaticArray and DynamicArray, this may aswell include multidimentional support.
	*
	* TODO: move conditional to its own module, it may need some tests too.
	* TODO: add multidimentional support to arrays, impliment StaticArray[][] & DynamicArray[][]
	*/

	template <typename T> class StaticArray;
	template <typename T> class DynamicArray;

#pragma region arrayAcronyms

	template <typename T> using sArr = StaticArray<T>;
	template <typename T> using dArr = DynamicArray<T>;

#pragma endregion

#pragma region ConditionalsImplimentaions
	// Implimentation Conditional --------------------------------------------------------------------------------------+
	template<bool B, typename X, typename Y> struct Conditional;							// To select between bool	|
	template<typename X, typename Y> struct Conditional< true, X, Y> { using type = X; };	// If first to be used		|
	template<typename X, typename Y> struct Conditional<false, X, Y> { using type = Y; };	// If second to be used		|
	// -----------------------------------------------------------------------------------------------------------------+
#pragma endregion

#pragma region staticArrayimplementation
	/**
	* @brief Statically Allocated Array (unresizable) each of size sizeof(T)
	*
	* @details
	* simple (non-resizeable) array that maintains information about its size and is capable of properly disposing its elements.
	* allows conversions from dynamic, vector, list, other arr types to static array.
	*
	* @tparam T  Type of the data stored in the list.
	*/
	template <typename T> class StaticArray {
	public:
		T* __container;							// To store elements in heap allocated array.
		int __size;								// To maintain information about length of array.
	public:
		StaticArray(int N);
		StaticArray(T* _A, int N);
		~StaticArray();
	public:
		int getSize() { return __size; }
		T& operator[](int index);
	public:
		template<typename U> friend DynamicArray<U> staticToDynamic(StaticArray<U>&);
		// TODO: impliment support for staticToVector	<T>
		// TODO: implement support for staticToList		<T>
		// TODO: implement support for staticTouLL		<T>
		// TODO: implement support for staticTobLL		<T>
	};

#pragma endregion

#pragma region dynamicArrayimplementation
	/**
	* @brief Dynamically Allocated Array (resizable) each of size sizeof(T)
	*
	* @details
	* (resizeable) array that maintains information about its size and is capable of properly disposing its elements.
	* allows conversions from static, vector, list, other arr types to static array.
	*
	* @tparam T  Type of the data stored in the list.
	*/
	template <typename T> class DynamicArray {
	protected:
		T* __container;							// To store elements in heap allocated array.
		int __size;								// To maintain information about length of array.
	public:
		DynamicArray();
		DynamicArray(T* _A, int N);
		~DynamicArray();
	public:
		int getSize() { return __size; }
		T& operator[](int index);
	public:
		void insert(T element);					// insert at last index.
		void insert(T element, int at);			// insert at specified index.
		void remove();							// remove at last index.
		void remove(int at);					// reomve at specified index.
	public:
		template<typename U> friend StaticArray<U> dynamicToStatic(DynamicArray<U>&);
		// TODO: impliment support for dynamicToVector		<T>
		// TODO: impliment support for dynamicToList		<T>
		// TODO: impliment support for dynamicTouLL 		<T>
		// TODO: impliment support for dynamicTobLL 		<T>
	};
#pragma endregion

#pragma region arrayManipulatorsDefinitions
	// Inter Array type conversions ------------------------------------------------------------------------------------+
	template<typename T> DynamicArray<T> staticToDynamic(StaticArray<T>&);	// staticArray -> dynamicArray				|
	template<typename T> StaticArray<T> dynamicToStatic(DynamicArray<T>&);	// dynamicArray -> staticArray				|
	// -----------------------------------------------------------------------------------------------------------------+
#pragma endregion

#pragma region arrayAlgorithms
	template<typename T> int BinarySearch(StaticArray<T>* _array, T _for);
	template<typename T> int BinarySearch(StaticArray<T>* _array, T _for, int (*comparision)(T, T));
#pragma endregion

};

#include "arrays.inl"

#pragma region arrayManipulatorsImplementations

template<typename T>
Structures::DynamicArray<T> Structures::staticToDynamic(Structures::StaticArray<T>& S) {
	return Structures::DynamicArray<T>(S.__container, S.__size);
}

template<typename T>
Structures::StaticArray<T> Structures::dynamicToStatic(Structures::DynamicArray<T>& D) {
	return Structures::StaticArray<T>(D.__container, D.__size);
}

#pragma endregion


#endif