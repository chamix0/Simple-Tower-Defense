#pragma once
#include "Observer.h"

class Publisher
{
private:
	TArray<Observer*> observers;

public:
	// Attach an observer
	void Subscribe(Observer* observer);

	// Detach an observer
	void Unsubscribe(Observer* observer);

	// Notify all observers
	void Notify(UTowerEvent message);
};
