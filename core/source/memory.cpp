#include "memory.h"

void Core::Memory::IObservableBase::attachObserver(IObserverBase* observer){
	__observers.push_back(observer);
}

void Core::Memory::IObservableBase::detachObserver(IObserverBase* observer){
	__observers.remove(observer);
}

void Core::Memory::IObservableBase::notifyObserver(IObserverBase* observer, const String& message){
	observer->eventUpdate(message);
}

Core::Memory::IObserverBase::IObserverBase(IObservableBase& subject) : __observable(subject) {
	this->__observable.attachObserver(this);
}

