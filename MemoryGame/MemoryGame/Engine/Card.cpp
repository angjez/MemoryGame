//Card class definition: constructor and setter function

#include "Card.h"

Card::Card()
{
	name = "";
	faceUp = false;
	matched = false;
}

void Card::setName(std::string name)
{ this->name = name; }


