#include "nodes.h"

template<typename T>
inline void Structures::uLinkedList<T>::attachR(T item){
	if (__tail != nullptr)
		__tail->setNext(new Structures::uNode<T>(item));
	else {
		__tail = new Structures::uNode<T>(item);
		__head = __tail;
	}
	__size++;
}

template<typename T>
inline void Structures::uLinkedList<T>::attachL(T item) {
	__head = new Structures::uNode<T>(item, __head);
	if (__tail == nullptr)
		__tail = __head;
	__size++;
}

template<typename T>
inline T& Structures::uLinkedList<T>::detachL(){
	if (__size == 0)
		throw Exceptions::ElementNotFound("Cannot detachLeft from an empty u-linked list")

	uNode<T>* __next = __head->getNext();
	T* __returnableT = __head->getItem();
	
	__head->setNext(nullptr);
	__head->setItem(nullptr);
	
	delete __head;

	if (__next == nullptr)
		__tail = nullptr;

	__head = __next;
	__size--;
	return __returnableT;
}

template<typename T>
inline T& Structures::uLinkedList<T>::detachR(){
	if (__size == 0)
		throw Exceptions::ElementNotFound("Cannot detachRight from an empty u-linked list")

	T* __returnableT = __tail->getItem();
	__tail->setItem(nullptr);
	delete __tail;

	uN<T>* __currentN = __head;
	while (__currentN->getNext() != nullptr) {
		__currentN = __currentN->getNext();
	}
	__tail = __currentN;
	__size--;
	return __returnableT;
}

template<typename T>
inline void Structures::uLinkedList<T>::insert(T item, int index){
	if (__size < index)
		throw Exceptions::IndexOutOfRange("Cannot insert at index > size in a linked list");
	
	if (index == 0) {
		this->attachL(item);
		return;
	}

	uN<T>* __currentN = __head;
	for (int i = 0; i < index; i++){
		__currentN = __currentN->getNext();
	}

	uN<T>* __insert = new uN<T>(item, __currentN->getNext());
	__currentN->setNext(__insert);
}

template<typename T>
inline T& Structures::uLinkedList<T>::remove(int index){
	if (__size <= index)
		throw Exceptions::IndexOutOfRange("Cannot remove from index >= size in a linked list");

	uN<T>* __currentN = __head;
	for (int i = 0; i < index-1; i++) {
		__currentN = __currentN->getNext();
	}

	uN<T>* __element = __currentN->getNext();
	__currentN->setNext(__element->getNext());
	T* __returnableT = __element->getItem();
	__element->setNext(nullptr);
	__element->setItem(nullptr);

	delete __element;
	return __returnableT;
}

template<typename T>
inline uN<T>& Structures::uLinkedList<T>::get(int index){
	if (__size <= index)
		throw Exceptions::IndexOutOfRange("Cannot get element at index >= size in a linked list");

	uN<T>* __currentN = __head;
	for (int i = 0; i < index; i++) {
		__currentN = __currentN->getNext();
	}

	return __currentN;
}



