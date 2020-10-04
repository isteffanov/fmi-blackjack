#pragma once
#include <iostream>
#include <cstring>


enum class Rank {
	Ace = 0,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eigth,
	Nine,
	Ten,
	J,
	Q,
	K,

	UNKNOWN = -1
};

enum class Suit{
	Clubs = 0,
	Diamonds,
	Spades,
	Hearts,

	UNKNOWN = -1
};

class Card
{
	const static char* const POSSIBLE_SERIAL_SYMBOLS;
	const static unsigned MAX_SERIAL_CARD = 15;

	Rank m_rank;
	Suit m_suit;

	char* m_serial;
	unsigned m_serlen;

private:
	void init(Rank rank, Suit suit, const char* serial);
	void generateSerial(unsigned length = 15);

public:
	Card();
	Card(Rank rank, Suit suit, const char* serial);
	Card(Card const& other);
	Card& operator=(Card const& other);
	~Card();

	bool operator==(Card const& other);

	Rank getRank() const;
	Suit getSuit() const;
	void setRank(unsigned rank);
	void setSuit(unsigned suit);

	void addPreffix(const char*& preffix, unsigned preffix_len); //adds the given cstring as a preffix to the serial
	void printCard() const;
};

