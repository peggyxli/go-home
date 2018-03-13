#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player
{
	private:
		std::string name;
		char icon;
		int location;
		bool stacked_status;
	public:
		Player();

		std::string getName() const {return name;}
		int getLocation() const {return location;}
		bool getStackedStatus() const {return stacked_status;}
		void setStackedStatus(bool val) {stacked_status = val;}

		void displayFrom(int);
		void moveMe(int);
		void switchPlacesWith(Player &);
		void moveToStart();

		bool isStackedOn(Player);
		bool operator> (const Player& b) const {return (location > b.location);}
		bool operator< (const Player& b) const {return (location < b.location);}
};

#endif // PLAYER_H
