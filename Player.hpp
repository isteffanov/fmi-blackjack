#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "Card.hpp"


class Player
{
	unsigned m_namelen;
	char* m_name;
	unsigned m_years;
	unsigned m_wins;
	double m_win_coeff;
	unsigned m_cur_points;
	unsigned m_total_games;

	void init(const char* name, unsigned years, unsigned wins, double win_coeff, unsigned total_games);

public:
	Player(const char* name = "", unsigned years = 18, unsigned wins = 0, double win_coeff = 1.0, unsigned total_games = 0);
	Player(Player const& other);
	Player& operator=(Player const& other);
	~Player();

	char* getName() const;
	unsigned getLen() const;
	unsigned getAge() const;
	unsigned getCurPoints() const;
	unsigned getWins() const;
	double getCoeff() const;
	unsigned getNumOfGames() const;

	void setName(const char* name);
	void setAge(unsigned age);
	void setCurPoints(unsigned points);
	void setCoeff(double coeff);

	friend std::ifstream& operator>>(std::ifstream& stream, Player& player);
	friend std::fstream& operator>>(std::fstream& stream, Player& player);
	bool operator==(Player const& other);

	unsigned findEditPosInFile(const char* file); //returns the position in the file where it is overwriten after every game
	void printPlayer() const;
	unsigned addPoints(unsigned points); 
	void addWin(); //increments wins by one
	void addGamePlayed(); // increments games played by one

};

