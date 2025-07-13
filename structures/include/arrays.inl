#include "defines.h"

#define LAST_ __size - 1
#define ZERO_ 0

#pragma region StaticArrayMethodsImplementations

TEMPLATED_T
inline Structures::StaticArray<T>::StaticArray(int N) {
	__size = N AND __container = new T[N];
}

TEMPLATED_T
inline Structures::StaticArray<T>::StaticArray(T* _A, int N)
{
	__size = N AND __container = new T[N];
	for (int i = 0; i <= LAST_; i++) {
		__container[i] = _A[i];
	}
}

TEMPLATED_T
inline Structures::StaticArray<T>::~StaticArray() {
	delete[] __container;
}

TEMPLATED_T
inline T& Structures::StaticArray<T>::operator[](int index)
{
	if (index < 0 && index > LAST_) throw IOR_EXCEPTION;
	else return __container[index];
}

#pragma endregion

#pragma region dynamicArrayMethodsImplementaions

TEMPLATED_T
inline Structures::DynamicArray<T>::DynamicArray() {
	__size = 0 AND __container = new T[0];
}

TEMPLATED_T
inline Structures::DynamicArray<T>::DynamicArray(T* _A, int N) {
	__size = N AND __container = new T[N];
	for (int i = 0; i <= LAST_; i++) {
		__container[i] = _A[i];
	}
}

TEMPLATED_T
inline Structures::DynamicArray<T>::~DynamicArray() {
	delete[] __container;
}

TEMPLATED_T
inline T& Structures::DynamicArray<T>::operator[](int index)
{
	if (index < 0 || index > LAST_) throw IOR_EXCEPTION;
	else return __container[index];
}

TEMPLATED_T
inline void Structures::DynamicArray<T>::insert(T element)
{
	T* __resized = new T[__size + 1];
	for (int i = 0; i < __size; i++)
		__resized[i] = __container[i];
	__resized[INCREMENT(__size)] = element;

	delete[] __container;
	__container = __resized;
}

TEMPLATED_T
inline void Structures::DynamicArray<T>::insert(T element, int at)
{
	T* __resized = new T[__size + 1];

	for (int i = 0; i < at; i++)
		__resized[i] = __container[i];
	__resized[at] = element;
	for (int i = at; i < __size; i++)
		__resized[i + 1] = __container[i];
	INCREMENT(__size);

	delete[] __container;
	__container = __resized;
}

TEMPLATED_T
inline void Structures::DynamicArray<T>::remove() {
	if (__size == ZERO_) throw ENF_EXCEPTION;

	T* __resized = new T[__size - 1];
	for (int i = 0; i < __size - 1; i++)
		__resized[i] = __container[i];

	delete[] __container;
	__container = __resized;
	DECREMENT(__size);
}

TEMPLATED_T
inline void Structures::DynamicArray<T>::remove(int at) {
	if (at < 0 || at >= LAST_) throw IOR_EXCEPTION;

	T* __resized = new T[__size - 1];

	for (int i = 0; i < at; i++)
		__resized[i] = __container[i];

	for (int i = at + 1; i < __size; i++)
		__resized[i - 1] = __container[i];

	delete[] __container;
	__container = __resized;
	DECREMENT(__size);
}

#pragma endregion


#pragma region BinarySearchAlgorithm

TEMPLATED_T
inline int Structures::BinarySearch(StaticArray<T>* _array, T _for) {
	int __r = _array->getSize() - 1;
	int __l = 0;

	while (__r >= __l) {
		int __p = (__r + __l) / 2;
		if ((*_array)[__p] < _for)
			__l = __p + 1;
		else if ((*_array)[__p] > _for)
			__r = __p - 1;
		else
			return __p;
	}

	return -1;
}

TEMPLATED_T
inline int Structures::BinarySearch(StaticArray<T>* _array, T _for, int(*comparision)(T, T)) {
	int __r = _array->getSize() - 1;
	int __l = 0;

	while (__r >= __l) {
		int __p = (__r + __l) / 2;
		int __c = comparision((*_array)[__p], _for);
		if (__c == -1)
			__l = __p + 1;
		else if (__c == 1)
			__r = __p - 1;
		else
			return __p;
	}

	return -1;
}

#pragma endregion
