
using namespace Structures;

template<typename T>
inline Structures::StaticArray<T>::StaticArray(int N){
	__c_length = N;
	__container = new T[__c_length];
}

template<typename T>
Structures::StaticArray<T>::StaticArray(T* _A, int N){
	__c_length = N;
	__container = new T[__c_length];
	for (int i = 0; i < N; i++){
		__container[i] = _A[i];
	}
}

template<typename T>
Structures::StaticArray<T>::~StaticArray(){
	delete[] __container;
}

template<typename T>
T& Structures::StaticArray<T>::operator[](int __idx){
	if (__idx >= 0 && __idx <= __c_length)
		return __container[__idx];
	throw std::out_of_range("index out of range");
}


template<typename T>
inline Structures::DynamicArray<T>::DynamicArray(){
	__c_length = 0;
	__container = new T[0];
}

template<typename T>
Structures::DynamicArray<T>::DynamicArray(T* _A, int N){
	__c_length = N;
	__container = new T[__c_length];
	for (int i = 0; i < N; i++) {
		__container[i] = _A[i];
	}
}

template<typename T>
Structures::DynamicArray<T>::~DynamicArray(){
	delete[] __container;
}

template<typename T>
T& Structures::DynamicArray<T>::operator[](int __idx){
	if (__idx >= 0 && __idx <= __c_length)
		return __container[__idx];
	throw std::out_of_range("index out of range");
}

template<typename T>
void Structures::DynamicArray<T>::insert(T element){
	T* __resized = new T[__c_length + 1];
	for (int i = 0; i < __c_length; i++)
		__resized[i] = __container[i];
	__resized[__c_length++] = element;
	delete[] __container;
	__container = __resized;
}

template<typename T>
void Structures::DynamicArray<T>::insert(T element, int at){
	T* __resized = new T[__c_length + 1];
	for (int i = 0; i < at; i++)
		__resized[i] = __container[i];
	__resized[at] = element;
	for (int i = at; i < __c_length; i++)
		__resized[i+1] = __container[i];
	__c_length += 1;
	delete[] __container;
	__container = __resized;
}

template<typename T>
void Structures::DynamicArray<T>::remove(){
	if (__c_length == 0)
		return;

	T* __resized = new T[__c_length - 1];
	for (int i = 0; i < __c_length - 1; i++)
		__resized[i] = __container[i];

	delete[] __container;
	__container = __resized;
	__c_length--;
}

template<typename T>
void Structures::DynamicArray<T>::remove(int at){
	if (at < 0 || at >= __c_length)
		return;

	T* __resized = new T[__c_length - 1];

	for (int i = 0; i < at; i++)
		__resized[i] = __container[i];

	for (int i = at + 1; i < __c_length; i++)
		__resized[i - 1] = __container[i];

	delete[] __container;
	__container = __resized;
	__c_length--;
}

