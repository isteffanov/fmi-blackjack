#pragma once
#include <iomanip>
#include <cstring>
#include <fstream>
#include "Deck.hpp"
#include "Player.hpp"

class Game
{
	static const char* db;
	Deck m_deck;
	Player m_player;

	char* getln();

	void updatePlayers(); //updates win and coefficient player data 
	bool displayAllPlayersData();
	bool choosePlayer(); //returns true if a player with the given name was found else returns false
	void writeNewPlayersData();
	void getNewPlayersData();
	void playerSetup(); // chooses the player or creates a new one

	unsigned evalPoints(Card const& card); // returns the points the given card is worth
	void calcCoeff(bool won); //updates the winning coefficient depending on whether the player won or not
	bool hit(); // returns true if the player busted
	void probs(Card const& first_card); // returns the probability of the player to get 21 on the next turn
	bool playerDraws(); //returns the value of hit at the end of the drawing
	unsigned dealerDraws(); // returns the dealers points at the end of the drawing
public:
	void begin();
};

