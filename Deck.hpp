#pragma once

#include "Card.hpp"

class Deck
{
	const static unsigned DEFAULT_SIZE = 52;
	const static unsigned MAX_SERIAL_DECK = 10;
	const static unsigned SHUFFLE_LEVEL = 64; //64

	Card* m_deck;
	unsigned m_capacity;

	char* m_serial;
	unsigned m_serlen;

private:
	void init(unsigned capacity, const char* serial);
	void fillDeck(unsigned cap, int cardsCreated = 0);
	void shuffle();

public:
	Deck();
	Deck(unsigned capacity, const char* serial = "Custom");
	Deck(Deck const& other);
	Deck& operator=(Deck const& other);
	~Deck();

	Card& operator[](unsigned i);
	unsigned getSize();

	Card draw(); //returns the first card and puts it last
	void swap(unsigned a, unsigned b);
	unsigned suitCount(Suit suit);
	unsigned rankCount(Rank rank);
	void printDeck() const;
};

