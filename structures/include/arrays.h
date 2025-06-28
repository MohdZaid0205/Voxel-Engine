#ifndef STRUCTURES_ARRAY_H
#define STRUCTURES_ARRAY_H

namespace Structures{

	/*
	* This file contains implimentation for StaticArray and DynamicArray, this may aswell include multidimentional support.
	* 
	* TODO: move conditional to its own module, it may need some tests too.
	* TODO: add multidimentional support to arrays, impliment StaticArray[][] & DynamicArray[][]
	*/

	// Implimentation Conditional --------------------------------------------------------------------------------------+
	template<bool B, typename X, typename Y> struct Conditional;							// To select between bool	|
	template<typename X, typename Y> struct Conditional< true, X, Y> { using type = X; };	// If first to be used		|
	template<typename X, typename Y> struct Conditional<false, X, Y> { using type = Y; };	// If second to be used		|
	// -----------------------------------------------------------------------------------------------------------------+

	template <typename T> class StaticArray;
	template <typename T> class DynamicArray;

	// StaticArray Implementation
	template <typename T> class StaticArray {
	public:
		T* __container;							// To store elements in heap allocated array.
		int __c_length;							// To maintain information about length of array.
	public:
		StaticArray(int N);
		StaticArray(T* _A, int N);
		~StaticArray();
	public:
		int getSize() { return __c_length; }
		T& operator[](int __idx);
	public:
		template<typename U> friend DynamicArray<U> staticToDynamic(StaticArray<U>&);
		// TODO: impliment support for vectorToStatic and listToStatic
	};

	// DynamicArray Implementation
	template <typename T> class DynamicArray {
	protected:
		T* __container;							// To store elements in heap allocated array.
		int __c_length;							// To maintain information about length of array.
	public:
		DynamicArray();
		DynamicArray(T* _A, int N);
		~DynamicArray();
	public:
		int getSize() { return __c_length; }
		T& operator[](int __idx);
	public:
		void insert(T element);					// insert at last index.
		void insert(T element, int at);			// insert at specified index.
		void remove();							// remove at last index.
		void remove(int at);					// reomve at specified index.
	public:
		template<typename U> friend StaticArray<U> dynamicToStatic(DynamicArray<U>&);
		// TODO: impliment support for vectorToDynamic and listToDynamic
	};


	// Inter Array type conversions ------------------------------------------------------------------------------------+
	template<typename T> DynamicArray<T> staticToDynamic(StaticArray<T>&);	// staticArray -> dynamicArray				|
	template<typename T> StaticArray<T> dynamicToStatic(DynamicArray<T>&);	// dynamicArray -> staticArray				|
	// -----------------------------------------------------------------------------------------------------------------+

	template<typename T> int BinarySearch(StaticArray<T>* _array, T _for);
	template<typename T> int BinarySearch(StaticArray<T>* _array, T _for, int (*comparision)(T,T));

}

#include "arrays.inl"


template<typename T>
Structures::DynamicArray<T> Structures::staticToDynamic(Structures::StaticArray<T>& S) {
	return Structures::DynamicArray<T>(S.__container, S.__c_length);
}

template<typename T>
Structures::StaticArray<T> Structures::dynamicToStatic(Structures::DynamicArray<T>& D) {
	return Structures::StaticArray<T>(D.__container, D.__c_length);
}

#endif