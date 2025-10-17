#include "defines.h"
#include "exceptions.h"
#include "memory.h"

TEMPLATED_T
inline Structures::Shared<T>::Shared()
{
	PTR_NULLI(__container);
	PTR_ALLOC(references,int(1));
}

TEMPLATED_T
inline Structures::Shared<T>::Shared(T object)
{
	PTR_ALLOC(__container,T(object));
	PTR_ALLOC(references,int(1));
}

TEMPLATED_T
inline Structures::Shared<T>::Shared(T* point)
{
	if(point)
		__container = point;
	else 
		PTR_NULLI(__container);
	PTR_ALLOC(references,int(1));
}

TEMPLATED_T
inline Structures::Shared<T>::~Shared()
{
	DECREMENT((*references));
	if(*references > 0) 
		EXIT;
	PTR_DELOC(__container);
	PTR_NULLI(__container);
	if (references)
		PTR_DELOC(references);
	PTR_NULLI(references);
}

TEMPLATED_T
inline Structures::Shared<T>::Shared(const Shared<T>& other)
{
	__container = other.__container;
	references  = other.references;
	INCREMENT((*references));
}

TEMPLATED_T
inline Structures::Shared<T>& Structures::Shared<T>::operator=(const Shared<T>& other)
{
	if (this == &other) return *this;
	DECREMENT((*references));
	__container = other.__container;
	references  = other.references;
	INCREMENT((*references));
	return *this;
}

TEMPLATED_T
inline T& Structures::Shared<T>::operator*() const
{
	if (__container)
		return *__container;
	throw MAV_EXCEPTION;
}

TEMPLATED_T
inline T* Structures::Shared<T>::operator->() const
{
	return __container;
}

template<typename T>
inline bool Structures::Shared<T>::operator==(Shared<T>& other)
{
	if(__container == other.__container)
		return true;
	return false;
}
