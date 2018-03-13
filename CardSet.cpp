#include <iostream>
#include <cstdlib> //used for rand()
#include <ctime> //used for time seeding
#include "CardSet.h"
using namespace std;

CardSet::CardSet(int num_cards, int max_card)
{	//Constructor; creates card set; assumes num_cards >= 2;
    this -> num_cards = num_cards;
    cards_array = new int[num_cards];
    cards_array[0] = -1; //guarantees at least one lost turn card
    cards_array[1] = 0; //guarantees at least one switch card

    srand((int)time(0)); //seeding random numbers with time
    for (int i = 2; i < num_cards; i++) //filling in other cards
        cards_array[i] = ((rand() % (max_card + 2)) - 1); // number between -1 and max_card
	card_index = 0;
}

CardSet::~CardSet()
{
	delete[] cards_array;
}

CardSet::CardSet(const CardSet& other)
{
	num_cards = other.num_cards;
	cards_array = new int[num_cards];
	for (int i = 0; i < num_cards; i++)
		cards_array[i] = other.cards_array[i];
}

CardSet CardSet::operator= (const CardSet& other)
{
	delete[] cards_array;
	num_cards = other.num_cards;
	cards_array = new int[num_cards];
	for (int i = 0; i < num_cards; i++)
		cards_array[i] = other.cards_array[i];
	return *this;
}

void CardSet::display()
{	//Purpose: displays card set
    cout << "\xC9";
    for (int i = 0; i < num_cards - 1; i++)
        cout << "\xCD" << "\xCB";
    cout << "\xCD" << "\xBB" << endl;

    cout << "\xBA";
    for (int i = 0; i < num_cards; i++)
    {
        if (cards_array[i] == 0)
            cout << "L";
        else if (cards_array[i] == -1)
            cout << "\xF7";
        else
            cout << cards_array[i];
        cout << "\xBA";
    }
    cout << endl;

    cout << "\xC8";
    for (int i = 0; i < num_cards - 1; i++)
        cout << "\xCD" << "\xCA";
    cout << "\xCD" << "\xBC" << endl;
}

void CardSet::shuffle()
{	//Purpose: shuffles card set
    int random_index; srand((int)time(0));
    int* new_array = new int[num_cards];

    for (int i = 0, j = num_cards; (j > 0); i++, j--)
    {
        random_index = (rand() % j);				//pick random card
        new_array[i] = cards_array[random_index];   //put card in new array
        cards_array[random_index] = cards_array[j-1];  //remove card from old array
    }

	for (int i = 0; i < num_cards; i++)
		cards_array[i] = new_array[i]; //copy information from new to old array
	delete[] new_array;

	cout << endl << "The cards have been shuffled:" << endl;
	display();
}

int CardSet::getNextCard()
{
	// Shuffling cards, if necessary
	if (card_index == num_cards)
	{
		cout << "The card stack is empty." << endl
			 << "The discarded cards will be shuffled." << endl;
		shuffle();
		cout << endl;
		card_index = 0;
	}
	card_index++;
	return cards_array[card_index-1];
}
