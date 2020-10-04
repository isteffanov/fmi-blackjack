#include <time.h>
#include "Deck.hpp"


Deck::Deck()
{
	init(DEFAULT_SIZE, "Default");
	
	fillDeck(m_capacity);

	//for (int i = 0; i < m_capacity; ++i)
	//	m_deck[i].addPreffix((const char*&)m_serial, m_serlen);
}

Deck::Deck(unsigned capacity, const char* serial)
{
	init(capacity, serial);

	fillDeck(m_capacity);

	//for (int i = 0; i < m_capacity; ++i)
	//	m_deck[i].addPreffix(serial, m_serlen);
}

Deck::Deck(Deck const& other)
{
	if (this != &other) {
		init(other.m_capacity, "Copy");

		for (int i = 0; i < m_capacity; ++i)
			m_deck[i] = other.m_deck[i];
	}
}

Deck& Deck::operator=(Deck const& other)
{
	if (this != &other) {
		delete[] m_deck;
		delete[] m_serial;

		init(other.m_capacity, "Copy=");

		for (int i = 0; i < m_capacity; ++i)
			m_deck[i] = other.m_deck[i];
	}
		
	return *this;
}

Deck::~Deck()
{
	delete[] m_deck;
	m_capacity = 0;

	delete[] m_serial;
	m_serlen = 0;
}

void Deck::init(unsigned capacity, const char* serial)
{
	m_capacity = capacity;
	m_deck = new Card[capacity];

	m_serlen = strlen(serial);
	if (m_serlen > MAX_SERIAL_DECK) m_serlen = MAX_SERIAL_DECK;
	m_serial = new char[m_serlen + 1];
	strncpy(m_serial, serial, m_serlen);
}

Card& Deck::operator[](unsigned i)
{
	if (i >= 0 && i < m_capacity) return m_deck[i];
	else throw std::out_of_range("index not in array bounds");
}

unsigned Deck::getSize()
{
	return m_capacity;
}

void Deck::fillDeck(unsigned cap, int cardsCreated)
{
	int card = cardsCreated;
	for (int i = 0; i < 13; ++i) {
		for (int j = 0; j < 4; ++j) {
			m_deck[card].setRank(i);
			m_deck[card].setSuit(j);
			card++;

			if (card == cap) {
				shuffle();
				return;
			}
		}
	}
	fillDeck(cap, card);
}

void Deck::swap(unsigned a, unsigned b)
{
	if (a >= m_capacity || b >= m_capacity) return;

	Card temp = m_deck[a];
	m_deck[a] = m_deck[b];
	m_deck[b] = temp;
}

unsigned Deck::suitCount(Suit suit)
{
	int counter = 0;
	for (int i = 0; i < m_capacity; ++i)
		if (m_deck[i].getSuit() == suit) counter++;

	return counter;
}

unsigned Deck::rankCount(Rank rank)
{
	unsigned counter = 0;
	for (int i = 0; i < m_capacity; ++i)
		if (m_deck[i].getRank() == rank) counter++;

	return counter;
}

void Deck::shuffle()
{
	srand(time(0));

	int breaker;
	long counter = m_capacity*SHUFFLE_LEVEL;
	do {
		breaker = rand() % SHUFFLE_LEVEL;
		counter--;
		int a = rand() % m_capacity;
		int b = rand() % m_capacity;
		if (a == b) continue;
		swap(a, b);
	} while (breaker != 0 || counter > 0);
}

Card Deck::draw()
{
	Card rtrn = m_deck[0];
	for (int i = 0; i < m_capacity - 1; ++i)
		m_deck[i] = m_deck[i + 1];
	m_deck[m_capacity - 1] = rtrn;
	return rtrn;
}

void Deck::printDeck() const
{
	for (int i = 0; i < m_capacity; ++i)
		m_deck[i].printCard();
}

