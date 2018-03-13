#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{ 	//Default constructor; includes prompt for name
	cerr << "Please enter a player name: ";
	getline(cin, name);
	icon = name[0];
	location = 0;
	stacked_status = false;
}

void Player::displayFrom (int print_position)
{
	if (print_position == 0)
		cout << "\n";
	cout << " ";
    while (print_position++ < location)
        cout << "  ";
    cout << icon;
}

void Player::moveMe(int num_moves)
{	//Purpose: moves the player's location "num_moves" spaces
	cout << name << " moves ";
	if (num_moves < 0)	{
		if (location + num_moves < 0)
			num_moves = -location;
		cout << "back " << -(num_moves) << " space";
	}
	else if (num_moves > 0)
		cout << "forward " << num_moves << " space";
	location += num_moves;

    if (num_moves > 1 || num_moves < -1)
        cout << "s";
    cout << "." << endl;
}

void Player::switchPlacesWith(Player &other_player)
{
	int temp_location = this->location;
    this->location = other_player.location;
    other_player.location = temp_location;

    cout << this->name << " switches locations with " << other_player.name << "." << endl;
}

bool Player::isStackedOn(Player other_player)
{
	bool return_value = false;
	if (this->location == other_player.location && other_player.name != this->name)
		{
			this->stacked_status = true;
			if (other_player.location != 0)
			{
				cout << this->name << " has landed on the same space as "
					 << other_player.name << "." << endl;
				return_value = true;
			}
		}
	return return_value;
}

void Player::moveToStart()
{
	cout << endl << this->name << " moves back to \x22Start.\x22" << endl;
	this->location = 0;
	this->stacked_status = false;
}
