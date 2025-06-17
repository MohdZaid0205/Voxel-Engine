#include "memory.h"

void Core::Memory::Base::IObservableBase::attachObserver(IObserverBase* observer){
	__observers.push_back(observer);
}

void Core::Memory::Base::IObservableBase::detachObserver(IObserverBase* observer){
	__observers.remove(observer);
}

void Core::Memory::Base::IObservableBase::notifyObserver(IObserverBase* observer, const String& message){
	observer->eventUpdate(message);
}

Core::Memory::Base::IObserverBase::IObserverBase(IObservableBase& subject) : __observable(subject) {
	this->__observable.attachObserver(this);
}

