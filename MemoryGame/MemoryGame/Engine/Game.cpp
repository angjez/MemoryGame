#include "Game.h"

//template use example
template<typename T>
void faceUp(T & a, T & b)
{
    a.faceUp = true;
    b.faceUp = true;
}
template<typename T>
void faceDown(T & a, T & b)
{
    a.faceUp = false;
    b.faceUp = false;
}

void Game::move(Deck & deck, int & count, int & points, int firstPos1, int firstPos2, int secPos1, int secPos2) {
        
        faceUp(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        
        
        if(deck.cards[firstPos1][firstPos2].name == deck.cards[secPos1][secPos2].name && !deck.cards[firstPos1][firstPos2].matched && !deck.cards[secPos1][secPos2].matched)
        {
//            a match
            deck.cards[firstPos1][firstPos2].matched = true;
            deck.cards[secPos1][secPos2].matched = true;
            count+=2;
            points+=5;
            faceUp(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        }
        else
        {
//            no match
            points-=1;
            faceDown(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        }
}
