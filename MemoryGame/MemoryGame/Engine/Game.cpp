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

void Game::move(Deck deck, int count, int points, int firstPos1, int firstPos2, int secPos1, int secPos2) {
    //Runs the game- the player is presented with the board until all matches are made
    //Flipping and comparing cards are simple tasks, so opted not to separate into smaller functions
    if(count!=36)
    {
        
        std::cout<<std::endl<< firstPos1 << " " << secPos1 << " " << firstPos2 << " " << secPos2 << " "  << std::endl;
        
        faceUp(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        
        
        if(deck.cards[firstPos1][firstPos2].name == deck.cards[secPos1][secPos2].name)
        {
//            a match
            count+=2;
            points+=5;
            deck.cards[firstPos1][firstPos2].matched = true;
            deck.cards[secPos1][secPos2].matched = true;
        }
        else
        {
//            no match
            points-=1;
            std::cout<<"Sorry, no match this time. You have "<<points<<" points.\n\n\n\n\n";
            faceDown(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
        }
    }

    if(count==36)
    {
        std::cout<<"Congratulations, you won! You have "<<points<<" points!\n";
    }
}
