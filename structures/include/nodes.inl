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

