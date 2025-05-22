#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H

#include "platform.h"
#include "pch.h"

namespace Core::Memory {

	template<typename Type> using Unique = std::unique_ptr<Type>;
	template<typename Type> using Shared = std::shared_ptr<Type>;
	template<typename Type> using Weak = std::weak_ptr<Type>;

	class IObservableBase;
	class IObserverBase;

	class IObservableBase {
		private:
			std::list<IObserverBase*> __observers;
		public:
			virtual CORE_API ~IObservableBase() { __observers.clear(); }
		public:
			void attachObserver(IObserverBase* observer);
			void detachObserver(IObserverBase* observer);
			void notifyObserver(IObserverBase* observer, const String& message);
	};

	class IObserverBase {
		private:
			IObservableBase& __observable;
		public:
			IObserverBase(IObservableBase& subject);
			virtual CORE_API ~IObserverBase() { __observable.detachObserver(this); }
		public:
			virtual CORE_API void eventUpdate(const String& message) = 0;
	};
};

#endif