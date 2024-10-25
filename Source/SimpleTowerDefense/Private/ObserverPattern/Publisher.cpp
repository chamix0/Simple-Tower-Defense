#include "SimpleTowerDefense/Public/ObserverPattern/Publisher.h"

void Publisher::Subscribe(Observer* observer)
{
	observers.Add(observer);
}

void Publisher::Unsubscribe(Observer* observer)
{
	// remove observer from the array
	observers.Remove(observer);
}

void Publisher::Notify(UTowerEvent message)
{
	for (Observer* observer : observers)
	{
		observer->update(message);
	}
}
