#include "nodes.h"

#define TEMPLATED_T template<typename T>
#define ENF_EXCEPTION Exceptions::ElementNotFound("Cannot remove element from empty LL.")
#define IOR_EXCEPTION Exceptions::IndexOutOfRange("Cannot find specifed `_index` in LL.")
#define INCREMENT __size++
#define DECREMENT __size--
#define ZERO_ 0
#define LAST_ __size - 1
#define AND ;
#define EXIT return

#pragma region uLinkedListMethods

TEMPLATED_T
inline void Structures::uLinkedList<T>::attachR(T item)
{
	if (__tail == nullptr)
		__tail = __head = new Structures::uNode<T>(item);
	else {
		__tail->setNext(new Structures::uNode<T>(item));
		__tail = __tail->getNext();
	}
	INCREMENT;
}

TEMPLATED_T
inline void Structures::uLinkedList<T>::attachL(T item)
{
	__head = new Structures::uNode<T>(item, __head);
	if (__size == ZERO_) __tail = __head;
	INCREMENT;
}

TEMPLATED_T
inline T& Structures::uLinkedList<T>::detachR()
{
	if (__size == 0) throw ENF_EXCEPTION;
	T* __returnValue = __tail->getItem();

	uN<T>* __parent = __head;
	while (__parent->getNext() != __tail) {
		__parent = __parent->getNext();
	}

	__tail->setItem(nullptr); delete __tail;
	__tail = __parent;
	DECREMENT;
	return __returnValue;
}

TEMPLATED_T
inline T& Structures::uLinkedList<T>::detachL()
{
	if (__size == 0) throw ENF_EXCEPTION;
	uNode<T>* __next = __head->getNext();
	T* __returnValue = __head->getItem();

	__head->setNext(nullptr);
	__head->setItem(nullptr);
	delete __head;

	if (__next == nullptr) __tail = nullptr;

	__head = __next;
	DECREMENT;

	return __returnValue;
}

TEMPLATED_T
inline void Structures::uLinkedList<T>::insert(T item, int index)
{
	if (__size > index) throw IOR_EXCEPTION;
	if (index == ZERO_) attachL(item) AND EXIT;
	if (index == LAST_) attachR(item) AND EXIT;

	uN<T>* __parent = __head;
	for (int i = 0; i < index; i++) {
		__parent = __parent->getNext();
	}

	__parent->setNext(new uN<T>(item, __parent->getNext()));
	INCREMENT;
}

TEMPLATED_T
inline T& Structures::uLinkedList<T>::remove(int index)
{
	if (index >= __size) throw IOR_EXCEPTION;
	if (index == ZERO_) return detachL();
	if (index == LAST_) return detachR();

	uN<T>* __parent = __head;
	for (int i = 0; i < index - 1; i++) {
		__parent = __parent->getNext();
	}

	uN<T>* __removable = __parent->getNext();
	__parent->setNext(__removable->getNext());
	T* __returnValue = __removable->getItem();
	__removable->setNext(nullptr);
	__removable->setItem(nullptr);

	delete __removable;
	DECREMENT;

	return __returnValue;
}

TEMPLATED_T
inline uN<T>& Structures::uLinkedList<T>::get(int index)
{
	if (__size > index) throw IOR_EXCEPTION;

	uN<T>* __returnable = __head;
	for (int i = 0; i < index - 1; i++) {
		__returnable = __returnable->getNext();
	}

	return __returnable;
}

#pragma endregion

#pragma region bLinkedListMethods

TEMPLATED_T
inline void Structures::bLinkedList<T>::attachR(T item)
{
	if (__tail == nullptr)
		__tail = __head = new Structures::bNode<T>(item);
	else {
		__tail->setNext(new Structures::bNode<T>(item, nullptr, __tail));
		__tail = __tail->getNext();
	}
	INCREMENT;
}

TEMPLATED_T
inline void Structures::bLinkedList<T>::attachL(T item)
{
	bN<T>* __item = new Structures::bNode<T>(item, __head, nullptr);
	if (__size == ZERO_) __tail = __head = __item;
	else __head->setPrev(__item) AND __head = __item;
	INCREMENT;
}

TEMPLATED_T
inline T& Structures::bLinkedList<T>::detachR()
{
	if (__size == 0) throw ENF_EXCEPTION;
	T* __returnValue = __tail->getItem();

	__tail = __tail->getPrev();
	__tail->getNext()->setItem(nullptr);
	__tail->getNext()->setPrev(nullptr);

	delete __tail->getNext();
	__tail->setNext(nullptr);
	DECREMENT;

	return __returnValue;
}

TEMPLATED_T
inline T& Structures::bLinkedList<T>::detachL()
{
	if (__size == 0) throw ENF_EXCEPTION;
	bNode<T>* __next = __head->getNext();
	T* __returnValue = __head->getItem();

	__head->setNext(nullptr);
	__head->setItem(nullptr);
	__next->setPrev(nullptr);

	delete __head;
	__head = __next;
	DECREMENT;

	return __returnValue;
}

TEMPLATED_T
inline void Structures::bLinkedList<T>::insert(T item, int index)
{
	if (__size > index) throw IOR_EXCEPTION;
	if (index == ZERO_) attachL(item) AND EXIT;
	if (index == LAST_) attachR(item) AND EXIT;

	bN<T>* __parent;
	if (index < size / 2) {
		__parent = __head;
		for (int i = 0; i < index; i++) {
			__parent = __parent->getNext();
		}
	}
	else {
		__parent = __tail;
		for (int i = __size; i > index; i--) {
			__parent = __parent->getPrev();
		}
	}

	__parent->setNext(new bN<T>(item, __parent->getNext(), __parent));
	__parent->getNext()->getNext()->setPrev(__parent->getNext());

	INCREMENT;
}

TEMPLATED_T
inline T& Structures::bLinkedList<T>::remove(int index)
{
	if (index >= __size) throw IOR_EXCEPTION;
	if (index == ZERO_) return detachL();
	if (index == LAST_) return detachR();

	bN<T>* __parent;
	if (index < size / 2) {
		__parent = __head;
		for (int i = 0; i < index; i++) {
			__parent = __parent->getNext();
		}
	}
	else {
		__parent = __tail;
		for (int i = __size; i > index; i--) {
			__parent = __parent->getPrev();
		}
	}

	bN<T>* __child = __parent->getNext()->getNext();
	T* __returnValue = __parent->getNext()->getItem();
	__parent->getNext()->setNext(nullptr);
	__parent->getNext()->setPrev(nullptr);
	__parent->getNext()->setItem(nullptr);
	delete __parent->getNext();
	__child->setPrev(__parent);
	__parent->setNext(__child);
	DECREMENT;

	return __returnValue;
}

TEMPLATED_T
inline bN<T>& Structures::bLinkedList<T>::get(int index)
{
	if (index >= __size) throw IOR_EXCEPTION;
	if (index == ZERO_) return __head;
	if (index == LAST_) return __tail;

	bN<T>* __parent;
	if (index < size / 2) {
		__parent = __head;
		for (int i = 0; i < index; i++) {
			__parent = __parent->getNext();
		}
	}
	else {
		__parent = __tail;
		for (int i = __size; i > index; i--) {
			__parent = __parent->getPrev();
		}
	}

	return __parent->getNext();
}

#pragma endregion
