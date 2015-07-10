#pragma once

#include <list>
#include "Observer.h"

class Subject {
public:
	virtual ~Subject() { mObservers.clear(); }
	virtual void Attach(Observer* o) { mObservers.push_back(o); }
	virtual void Detach(Observer* o) { mObservers.remove(o); }
	virtual void Notify()
	{
		std::list<Observer*>::iterator it = mObservers.begin();
		while (it != mObservers.end()){
			(*it)->Update(this);
			it++;
		}
	}
protected:
	Subject() {}
private:
	std::list<Observer*> mObservers;
};