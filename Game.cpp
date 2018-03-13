#include <iostream>
#include <string>
#include <cstdlib> //used for rand()
#include <ctime> //used for time seeding
#include <sstream> // used to convert int to string
#include <vector>
#include <algorithm> //used for sort
#include "Player.h"
#include "Game.h"
#include "CardSet.h"
using namespace std;

Game::Game(): cards(NUMBER_OF_CARDS, MAX_CARD_VALUE)
{	//Default constructor; sets up game
    displayHeader(1, "Game GoHome!");
    displayHeader(2, "Rules");
    displayRules();
    cout << endl;

    displayHeader(1, "Setting Up");
    displayHeader(2, "Board");
    board_vector = generateBoard(MAX_BOARD_SIZE);
    displayBoard(board_vector);
    cout << endl;

    displayHeader(2, "Cards");
    cards.display();
    cards.shuffle();
    cout << endl;

    displayHeader(2, "Players");
    players = readPlayers(MAX_PLAYERS);
    cout << endl;
    cout << "The players have been placed on the board:" << endl;
    displayPlayers(players);
    displayBoard(board_vector);
    cout << endl;
}


void Game::displayHeader(int header_type, string header_name)
{	//Purpose: display console-wide header
    unsigned int padding, i = 0;
    padding = (78-header_name.length())/2;

    if (header_type == 1)
    {
    //  Top row
        cout << "\xC9";
        for (i = 0; i < ((padding-1)*2 + header_name.length()); i++)
            cout << "\xCD";
        cout << "\xBB" << endl;

    //  Middle row with padding & centered text
        cout << "\xBA";
        for (i = 0; i < padding-1; i++)
            cout << " ";
        cout << header_name;
        for (i = 0; i < padding-1; i++)
            cout << " ";
        cout << "\xBA" << endl;

    //  Bottom row
        cout << "\xC8";
        for (i = 0; i < ((padding-1)*2 + header_name.length()); i++)
            cout << "\xCD";
        cout << "\xBC" << endl;
    }
    else if (header_type == 2)
    {
    //  Left side padding
        for (i = 0; i < padding/2; i++)
            cout << "- ";

    //  Center with text
        if (padding % 2 == 1) //checking to see if padding is odd or even
            cout << "-" << header_name << "-"; //adds extra characters if odd
        else
            cout << header_name;

    //  Right side padding
        for (i = 0; i < padding/2; i++)
            cout << " -";

        cout << endl;
    }
    return;
}


void Game::displayRules (void)
{	//Purpose: display rules
    cout << "Number of Players: 2-6" << endl << endl
         << "Object of the Game" << endl
            << "    -To reach the last space on the board, labeled 'H' for 'Home.'" << endl << endl
         << "Setting Up" << endl
            << "    -Players will be sorted according to name length." << endl
            << "    -The player with the shortest name will go first," << endl
            << "     followed by the player with the next shortest name." << endl
            << "    -If two or more players have names of the same length, turn order" << endl
            << "     among these players will be determined by name entry order." << endl << endl
         << "Gameplay" << endl
            << "    -At the beginning of each turn, the player will select a card." << endl
                << "\t-If the card selected is an 'L' card, the player will lose a turn," << endl
                << "\t and gameplay will pass to the next player." << endl
                << "\t-If the card selected is a '\xF7' card, the player will switch locations" << endl
                << "\t with another player." << endl
                << "\t-If the card selected is a numeric card, the player will move forward" << endl
                << "\t the number of spaces on the card." << endl
            << "    -After moving, if the player lands on a tile with a number, the player" << endl
            << "     will move back that number of spaces"<< endl;
    return;
}


vector <int> Game::generateBoard(int max_board_size) //fix output for rounding and 1-1
{	//Purpose: create board vector
//  Reading board specifications
	int board_size = readIntVarInfo("number of spaces", 2, max_board_size);
	int num_obstacles = readIntVarInfo("number of obstacles", 1, (board_size/3));
    int max_obstacle_value = readIntVarInfo("largest obstacle value", 1, (board_size/4));
    cout << "Your board has " << board_size << " spaces, " << num_obstacles << " obstacles, "
         << "and a maximum obstacle value of " << max_obstacle_value << "." << endl;

    vector <int> board_vector (board_size, 0);
    int random_index = 0; srand((int)time(0));    //seeding random numbers with time

	while (num_obstacles > 0)
	{
		random_index = (rand() % (board_size-2)) + 1;
		if (board_vector[random_index] == 0)
		{
			board_vector[random_index] = (rand() % max_obstacle_value) + 1;
			if (board_vector[random_index] > random_index)
                board_vector[random_index] = random_index;
			num_obstacles--;
		}
	}

	for (int i = 1; i < (board_size-1); i++)
        if (board_vector[i] == 0)
            if (((rand() % 10) + 1) < 3)
                board_vector[i] = -1;

	return board_vector;
}


int Game::readIntVarInfo(string item_descriptor, int min_num, int max_num)
{	//Purpose: checks variable for errors
    int item_variable = 0;
    cout << "Please select the " << item_descriptor << " (" << min_num << "-" << max_num << "): ";
    cin >> item_variable;
    cout << endl;

    while (item_variable < min_num || item_variable > max_num)
    {
		if (item_variable < min_num)
            cout << "ERROR: The minimum " << item_descriptor << " is " << min_num << "." << endl;
        else
	    	cout << "ERROR: The maximum " << item_descriptor << " is " << max_num << "." << endl;

		cout << "Please enter a valid " << item_descriptor << ": ";
		cin >> item_variable;
		cout << endl;
	}
	return item_variable;
}


void Game::displayBoard(vector <int> board_vector)
{	//Purpose: displays game board
//  Top row
    cout << "\xDA";
    for (int i = 0; i < board_vector.size() - 1; i++)
        cout << "\xC4" << "\xC2";
    cout << "\xC4" << "\xBF" << endl;

//  Middle row with tile/space values
    cout << "\xB3" << "S" << "\xB3";
    for (int i = 1; i < board_vector.size() - 1; i++)
    {
        if (board_vector[i] == 0)
            cout << " ";
        else if (board_vector[i] == -1)
            cout << "G";
        else
            cout << board_vector[i];
        cout << "\xB3";
    }
    cout << "H" << "\xB3" << endl;

//  Bottom row
    cout << "\xC0";
    for (int i = 0; i < board_vector.size() - 1; i++)
        cout << "\xC4" << "\xC1";
    cout << "\xC4" << "\xD9" << endl;

    return;
}


vector <Player> Game::readPlayers(int max_players) //fix output
{	//Purpose: create and sort player vector
    vector <Player> players; char choice;

//	Players 1 & 2
	cin.ignore();
	players.push_back(Player());
	players.push_back(Player());

//	Players 3+
	cerr << endl << "Would you like to enter another player (Y/N)? ";
	cin >> choice;
    while ((choice=='Y'|| choice=='y') && players.size() <= max_players)
    {
		cin.ignore();
		players.push_back(Player());
		cerr << endl << "Would you like to enter another player (Y/N)? ";
		cin >> choice;
    }

//	Printing player names
    cout << "The players read in are: ";
    for (int i = 0; i < players.size()-1; i++) cout << players[i].getName() << ", ";
    cout << "and " << players.back().getName() << "." << endl << endl;

    sort(players.begin(), players.end(), sortPlayerLength);
    cout << "The player order is: ";
    for (int i = 0; i < players.size()-1; i++) cout << players[i].getName() << ", ";
    cout << "and " << players.back().getName() << "." << endl << endl;

    return players;
}


void Game::displayPlayers(vector <Player> players)
{	//Purpose: display location of players; used with displayBoard()
	int stacked_player = -1, i = 0;
	sort(players.begin(), players.end(), sortPlayerLocation); //easier printing
	for (int i = 0; i < players.size()-1; i++)
		if (players[i].getLocation() == players[i+1].getLocation())
		{
			players[i].setStackedStatus(true);
			if (players[i].getLocation() != 0)
				stacked_player = i;
		}

	if (stacked_player != -1 && players[0].getStackedStatus() == false)
	{
		players[stacked_player].displayFrom(0);
		players.erase(players.begin() + stacked_player);
		stacked_player = -1;
	}
	else if (players[0].getStackedStatus() == true)
	{
		for (i = 0; (i < players.size()-1 && players[i+1].getLocation() == 0); i++)
		{
			players[i].displayFrom(0);
			if (i < players.size()-2) //to avoid out of bounds
				if (players[i+2].getLocation() != 0 && stacked_player != -1)
				{
					players[stacked_player].displayFrom(players[i].getLocation()+1);
					players.erase(players.begin()+i+1);
					stacked_player = -1;
				}
		}
	}

	players[i].displayFrom(0);
	for (i++; i < players.size(); i++)
		players[i].displayFrom(players[i-1].getLocation()+1);
	cout << endl;
}


void Game::play()
{	//Purpose: plays the game
    int turn_num = 1, current = 0;
    bool player_won = false;
    string turn_message = " ", winning_message = " has won the game!";
    stringstream ss;
    ss.clear();

	displayHeader(1, "Let's play!");
    cout << endl;

    do {
    //  Printing turn header
        ss.str ("");
        ss << "Turn #" << turn_num << ": " << players[current].getName();
        turn_message = ss.str();
        displayHeader(2, turn_message);
        cout << endl;

    //  Taking a turn
		takeTurn(board_vector, cards.getNextCard(), players, current);

    //  Passing turn to next player or ending game
        if (players[current].getLocation() == board_vector.size()-1)   //checking if player is on 'H' tile
            player_won = true;  //ending do-while loop/game
        else
        {
            cout << endl;
            turn_num++;

        //  Passing turn to next player
            if (board_vector[players[current].getLocation()] == -1)
                cout << players[current].getName() << " has landed on a Go Again! space." << endl;
            else if (current == players.size() - 1)
                current = 0;
            else
                current++;
        }
    }   while (!player_won);

//  Declaring winner
    cout << endl;
    winning_message.insert(0, players[current].getName());
    displayHeader(1, winning_message);
    return;
}


void Game::takeTurn(vector <int> board_vector, int card_value, vector <Player> &players, int current)
{	//Purpose: takes a turn for the player
    moveFromCard(card_value, board_vector, players, current);

	if (card_value > 0)
	{
		for (int i = 0; i < players.size(); i++)
			if (players[current].isStackedOn(players[i]))
			{
				displayPlayers(players); displayBoard(board_vector);
				players[i].moveToStart();
				displayPlayers(players); displayBoard(board_vector);
			}

		if (board_vector [players[current].getLocation()] > 0)
		{
			cout << endl;
			cout << players[current].getName() << " has landed on an obstacle." << endl;
			players[current].moveMe(-(board_vector[players[current].getLocation()]));
			cout << endl;
			displayPlayers(players); displayBoard(board_vector);

			for (int i = 0; i < players.size(); i++)
				if (players[current].isStackedOn(players[i]))
				{
					displayPlayers(players); displayBoard(board_vector);
					players[i].moveToStart();
					displayPlayers(players); displayBoard(board_vector);
				}
		}
	}
}


void Game::moveFromCard(int card_value, vector <int> board, vector <Player> &players, int current)
{	//Purpose: reads a card and moves the player accordingly
	if (card_value == -1)
    {
        cout << players[current].getName() << " has selected a \xF7 card." << endl;
        switchPlaces(current, players);
    }
	else if (card_value == 0)	{
        cout << players[current].getName() << " has selected a L card." << endl
             << players[current].getName() << " loses a turn." << endl;
    }
    else	{
        cout << players[current].getName() << " has selected a "
             << card_value << " card." << endl;

        if ((players[current].getLocation() + card_value) > board.size()-1)
        {
        	int remaining_moves = (card_value - ((board.size()-1) - players[current].getLocation()));
        	players[current].moveMe((board.size()-1) - players[current].getLocation());
        	cout << players[current].getName() << " has reached \x22Home.\x22" << endl;
        	displayPlayers(players);
			displayBoard(board);

			cout << players[current].getName() << " still has " << remaining_moves
				 << " out of " << card_value << " moves remaining." << endl;
			players[current].moveMe(-(remaining_moves));
        }
        else
        	players[current].moveMe(card_value);
    }
    displayPlayers(players);
	displayBoard(board);
}


void Game::switchPlaces(int current, vector <Player> &players)
{	//Purpose: switches location of one player with another
    srand((int)time(0));
	int player_to_switch = findMaxIndex(players, current);

// Correcting errors
	if (player_to_switch == 0 && players[0].getLocation() == 0)	//should only occur when all are at start
		player_to_switch = rand() % players.size();	//so the same person doesn't get swapped every time
	while (player_to_switch == current)	//so current player does not switch with themselves
		player_to_switch = rand() % players.size();

	players[current].switchPlacesWith(players[player_to_switch]);
}
