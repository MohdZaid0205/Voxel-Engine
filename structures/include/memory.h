#ifndef STRUCTURES_MEMORY_H
#define STRUCTURES_MEMORY_H

namespace Structures{
	
#pragma region basicInformation
	// this is to declare basic memory management for structures that requires it, this file will contain
	// implementations of unique_ptr, shared_ptr and weak_refernces, i may end up making strong and weak refernces.
	// as of now 2 things are fixed only Unique and Shared

	template<typename T> class Shared;
	template<typename T> class Unique;
#pragma endregion

#pragma region sharedPointerImplementation
	/**
	* @brief make a pointer that could be shared across elements that need it
	*
	* @details
	* A simple shared pointer class for managing shared ownership of a dynamically allocated object.
	* The object is automatically deallocated when the last shared reference to it is destroyed.
	* Only strong references are counted
	* @tparam T  Type of the data stored shared memory.
	*/
	template<typename T> class Shared{
	private:
		T* __container;         // Pointer to the object being managed
		int* references;        // Pointer to the reference count (shared across instances)
	public:
		Shared();				// Constructor: to make empty shared object
		Shared(T object);       // Constructor: create a shared pointer from a value
		Shared(T* point);       // Constructor: create a shared pointer from an existing raw pointer
		~Shared();              // Destructor: decrement ref count and delete if this is the last owner
	public:
		Shared(const Shared<T>& reference);            // Copy constructor: increases ref count
		Shared<T>& operator=(const Shared<T>& other);  // Copy assignment: properly manage ownership
	public:
		T& operator*() const;   // Dereference operator: access the underlying object
		T* operator->() const;  // Arrow operator: access members of the underlying object
	public:
		bool operator==(Shared<T>& other);
	};
#pragma endregion

}

#include "memory.inl"

#endif