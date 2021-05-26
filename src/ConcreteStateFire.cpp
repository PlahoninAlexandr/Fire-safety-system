#include "Arduino.h"
#include "ConcreteStateFire.h"

void ConcreteStateFire::Fire()
{

	digitalWrite(D1, LOW);
	digitalWrite(D2, HIGH);
	std::cout << "!!!!FIRE!!!!\n";

	this->context_->TransitionTo(new ConcreteStateAnnounce, "ConcreteStateAnnounce");
}

