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

void Game::startGame(Deck deck) {
    //Runs the game- the player is presented with the board until all matches are made
    //Flipping and comparing cards are simple tasks, so opted not to separate into smaller functions

    int count =0, points=0;
    std::string next;
    int firstPos1, firstPos2, secPos1, secPos2;
    std::cout<<"Welcome to MemoryGame!\n";
    while(count!=36)
    {
        deck.print();
        std::cout<<"\n Enter the coordinates of two cards you would like to flip.\n Use the format \"x,y+x,y\". Do not add any extra spaces or characters.\n";
        std::cin>>next;
        
        std::cout << next[0] << " " << next[2] << " " << next[4] << " " << next[6] << " " << std::endl;

        firstPos1=next[0] - 48;
        firstPos2=next[2] - 48;
        secPos1=next[4] - 48;
        secPos2=next[6] - 48;
        std::cout << firstPos1 << " " << firstPos2 << " " << secPos1 << " " << secPos2 << std::endl;

    //Make sure player chooses cards on the board
//        exeptions usage
        try {
            if(firstPos1>5||firstPos1<0||firstPos2>5||firstPos2<0||secPos1>5||secPos1<0||secPos2>5||secPos2<0)
                throw 1;

            else
            {
                faceUp(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
                deck.print();
            if(deck.cards[firstPos1][firstPos2].name == deck.cards[secPos1][secPos2].name)
            {
                count+=2;
                points+=5;
                std::cout<<"It's a match! You have "<<points<<" points!\n\n\n\n\n";
                deck.cards[firstPos1][firstPos2].matched = true;
                //When cards are marked as matched, they will only display [  O  ], even if the player selects that card again
                deck.cards[secPos1][secPos2].matched = true;
            }
            else
            {
                points-=1;
                std::cout<<"Sorry, no match this time. You have "<<points<<" points.\n\n\n\n\n";
                faceDown(deck.cards[firstPos1][firstPos2], deck.cards[secPos1][secPos2]);
            }
                
            }
        }
        catch(int i) {
            if (i == 1)
                std::cout<<"Invalid position! Try again!\n\n";
        }
    }

    if(count==36)
    {
        std::cout<<"Congratulations, you won! You have "<<points<<" points!\n";
    }
}
