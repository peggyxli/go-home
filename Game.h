#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "Player.h"
#include "CardSet.h"

class Game
{
	private:
		const int MAX_BOARD_SIZE = 38; // must be 2 or larger
		const int NUMBER_OF_CARDS = 10;
		const int MAX_CARD_VALUE = 9; //highest numeric value on cards
		const int MAX_PLAYERS = 6;

		std::vector <int> board_vector;
		CardSet cards;
		std::vector <Player> players;
	public:
		Game();
		void displayHeader(int, std::string);
		void displayRules (void);
		int readIntVarInfo(std::string, int, int);
		std::vector <int> generateBoard(int);
		void displayBoard(std::vector <int>);

		std::vector <Player> readPlayers(int);
		void displayPlayers(std::vector <Player>);
		static bool sortPlayerLength (const Player &lhs, const Player &rhs)
			{ return lhs.getName().length() < rhs.getName().length(); }
		static bool sortPlayerLocation (const Player &lhs, const Player &rhs)
			{ return lhs.getLocation() < rhs.getLocation(); }

		void play();
		void takeTurn(std::vector <int>, int, std::vector <Player> &, int);
		void moveFromCard(int, std::vector <int>,  std::vector <Player> &, int);
		void switchPlaces(int, std::vector <Player> &);

		template <class T>
		int findMaxIndex (const std::vector <T> & vec, int ignore_index = -1)
		{
			int max_index = 0;
			for (unsigned int i = 1; i < vec.size(); i++)	//start at 1 because max_index is 0
				if (i != ignore_index && vec[i] > vec[max_index])
					max_index = i;
			return max_index;
		}
};

#endif // GAME_H
