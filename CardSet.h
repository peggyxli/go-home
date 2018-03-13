#ifndef CARDSET_H
#define CARDSET_H

class CardSet
{
	private:
		int* cards_array;
		int num_cards;
		int card_index;
	public:
		CardSet(int, int);
		~CardSet();
		CardSet(const CardSet& other);
		CardSet operator= (const CardSet& other);
		void display();
		void shuffle();
		int getNextCard();
};

#endif // CARDSET_H
