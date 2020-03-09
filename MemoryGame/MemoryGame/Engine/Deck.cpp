//Deck class definition

#include "Deck.h"

Deck::Deck()
{}

void Deck::addCards(std::string fileName)
{
	//Read card names off file given in main driver into a vector
	//The vector is shuffled and copied into a 2D array of Cards
	//This ensures a different grid each time

// STL container use
	std::vector<std::string> names;
	std::ifstream cardFile;
	std::string line;
	int count(0);

	cardFile.open(fileName);
	if(cardFile.fail())
	{ 
		std::cerr<<"Could not open file!\n";
		exit(1);
	}

	while(!cardFile.eof())
	{
		getline(cardFile, line);
		if(line!=""&&line!="\n"&&line!="\t"&&line!=" ")
		{ names.push_back(line); }
	}
	
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
// STL algorythm use
	std::shuffle(names.begin(), names.end(), std::default_random_engine(seed));

	cards[0][0].setName(names[count]);
	for(int i=0; i<COLS; i++)
	{
		for(int j=0; j<ROWS; j++)
		{
			cards[i][j].setName(names[count]);
            std::cout << cards[i][j].name << std::endl;
			count++;
		}
        std::cout<< std::endl;
	}
	cardFile.close();
}
