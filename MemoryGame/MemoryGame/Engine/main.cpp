#include "Deck.h"
#include "Card.h"
#include "Game.h"
#include "GameDisplay.h"
#include <iostream>
#include <stdio.h>


int main(int argc, char * argv[])
{
    Deck deck;
    deck.addCards("cards.txt");
    initiateDisplay(deck);
	return(0);
}
