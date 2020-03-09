#include "Game.hpp"

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
    //Runs the game- the player is presented with the board until all matches are made
    //Flipping and comparing cards are simple tasks, so opted not to separate into smaller functions
        std::cout<<std::endl<< deck.cards[firstPos1][firstPos2].name << " " << deck.cards[secPos1][secPos2].name << " "  << std::endl;
        
        faceUp(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        
        
        if(deck.cards[firstPos1][firstPos2].name == deck.cards[secPos1][secPos2].name)
        {
//            a match
            std::cout<<std::endl<< "match"<< std::endl;
            count+=2;
            points+=5;
            faceUp(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        }
        else
        {
//            no match
            std::cout<<std::endl<< "no match"<< std::endl;
            points-=1;
            faceDown(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        }
        std::cout<<std::endl<< count << std::endl;
}
