#include "Card.hpp"

const char* const Card::POSSIBLE_SERIAL_SYMBOLS = "1234567890abcdefghijklmnopqrstuvwxyz";

Card::Card()
{
	m_rank = Rank::UNKNOWN;
	m_suit = Suit::UNKNOWN;

	generateSerial();
}

Card::Card(Rank rank, Suit suit, const char* serial)
{
	init(rank, suit, serial);
}

Card::Card(Card const& other) 
{
	if (this != &other) {
		init(other.m_rank, other.m_suit, other.m_serial);
	}
}

Card& Card::operator=(Card const& other)
{
	if (this != &other) {
		delete[] m_serial;
		init(other.m_rank, other.m_suit, other.m_serial);
	}
	
	return *this;
}

Card::~Card()
{
	delete[] m_serial;
	m_serlen = 0;
}

void Card::init(Rank rank, Suit suit, const char* serial)
{
	m_rank = rank;
	m_suit = suit;

	m_serlen = strlen(serial);
	if (m_serlen > MAX_SERIAL_CARD) m_serlen = MAX_SERIAL_CARD;
	m_serial = new char[m_serlen + 1];
	strncpy(m_serial, serial, m_serlen);
}

bool Card::operator==(Card const& other)
{
	if (m_serlen != other.m_serlen) return false;
	else return !strncmp(m_serial, other.m_serial, m_serlen);
}


void Card::generateSerial(unsigned length)
{
	if (length > MAX_SERIAL_CARD) length = MAX_SERIAL_CARD;
	m_serial = new char[length + 1];
	int num_of_possible_symbols = strlen(POSSIBLE_SERIAL_SYMBOLS);

	for (int i = 0; i < length; ++i)
		m_serial[i] = POSSIBLE_SERIAL_SYMBOLS[rand() % num_of_possible_symbols];
	m_serial[length] = '\0';
	
}

Rank Card::getRank() const
{
	return m_rank;
}

Suit Card::getSuit() const
{
	return m_suit;
}

void Card::setRank(unsigned rank)
{
	switch (rank){
	case 0:
		m_rank = Rank::Ace;
		return;
	case 1:
		m_rank = Rank::Two;
		return;
	case 2:
		m_rank = Rank::Three;
		return;
	case 3:
		m_rank = Rank::Four;
		return;
	case 4:
		m_rank = Rank::Five;
		return;
	case 5:
		m_rank = Rank::Six;
		return;
	case 6:
		m_rank = Rank::Seven;
		return;
	case 7:
		m_rank = Rank::Eigth;
		return;
	case 8:
		m_rank = Rank::Nine;
		return;
	case 9:
		m_rank = Rank::Ten;
		return;
	case 10:
		m_rank = Rank::J;
		return;
	case 11:
		m_rank = Rank::Q;
		return;
	case 12:
		m_rank = Rank::K;
		return;
	default:
		m_rank = Rank::UNKNOWN;
		return;
	}
}

void Card::setSuit(unsigned suit)
{
	switch (suit) {
	case 0:
		m_suit = Suit::Clubs;
		return;
	case 1:
		m_suit = Suit::Diamonds;
		return;
	case 2:
		m_suit = Suit::Spades;
		return;
	case 3:
		m_suit = Suit::Hearts;
		return;
	default:
		m_suit = Suit::UNKNOWN;
		break;
	}
}

void Card::addPreffix(const char*& preffix, unsigned preffix_len)
{
	char* temp = new char[m_serlen + preffix_len + 1];

	strcpy(temp, preffix);
	strcat(temp, m_serial);

	delete[] m_serial;

	m_serlen += preffix_len;
	temp[m_serlen] = '\0';

	m_serial = temp;
	temp = nullptr;
}

void Card::printCard() const
{
	std::cout << "The ";

	switch (m_rank) {
	case Rank::Ace:
		std::cout << "Ace";
		break;
	case Rank::Two:
		std::cout << "Two";
		break;
	case Rank::Three:
		std::cout << "Three";
		break;
	case Rank::Four:
		std::cout << "Four";
		break;
	case Rank::Five:
		std::cout << "Five";
		break;
	case Rank::Six:
		std::cout << "Six";
		break;
	case Rank::Seven:
		std::cout << "Seven";
		break;
	case Rank::Eigth:
		std::cout << "Eigth";
		break;
	case Rank::Nine:
		std::cout << "Nine";
		break;
	case Rank::Ten:
		std::cout << "Ten";
		break;
	case Rank::J:
		std::cout << "Jack";
		break;
	case Rank::Q:
		std::cout << "Queen";
		break;
	case Rank::K:
		std::cout << "King";
		break;
	default:
		std::cout << "Unknown";
	}

	std::cout << " of ";

	switch (m_suit) {
	case Suit::Clubs:
		std::cout << "Clubs";
		break;
	case Suit::Diamonds:
		std::cout << "Diamonds";
		break;
	case Suit::Spades:
		std::cout << "Spades";
		break;
	case Suit::Hearts:
		std::cout << "Hearts";
		break;
	default:
		std::cout << "Unknown";
	}
}
