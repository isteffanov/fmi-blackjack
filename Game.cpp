#include "Game.hpp"

const char* Game::db = "players.bin";	

char* Game::getln()
{
	int size = 0;
	unsigned cap = 4;
	char* buf = new char[cap];
	
	char c;
	std::cin.get(c);
	while (c != '\n') {
		if (std::cin.good()) {
			if (size < cap) {
				buf[size] = c;
				size++;
				std::cin.get(c);
			}
			else {
				cap *= 2;
				char* temp = new char[cap];
				strncpy(temp, buf, size);
				delete[] buf;
				buf = temp;
				temp = nullptr;
				buf[size] = c;
				size++;
				std::cin.get(c);
			}
		}
		else break;
	}

	char* rtrn = new char[size + 1];
	strncpy(rtrn, buf, size);
	delete[] buf;
	rtrn[size] = '\0';

	return rtrn;
}

void Game::updatePlayers()
{
	int pos = m_player.findEditPosInFile(db);
	std::fstream file(db, std::ios::binary | std::ios::out | std::ios::in);
	if (file.is_open()) {
		file.seekp(pos);
		unsigned wins = m_player.getWins();
		double coeff = m_player.getCoeff();
		unsigned games = m_player.getNumOfGames();

		file.write((char*)&wins, sizeof(unsigned));
		file.write((char*)&coeff, sizeof(double));
		file.write((char*)&games, sizeof(unsigned));
	}
}

bool Game::displayAllPlayersData()
{
	std::ifstream ifile(db, std::ios::binary);
	int no = 0;
	while (!ifile.eof()) {
		Player player;
		ifile >> player;
		if (ifile.good()) {
			no++;
			std::cout << no << ":"; 
			player.printPlayer();
		}
	}
	if (no == 0) return false;
	return true;
}

bool Game::choosePlayer()
{
	std::cout << "\nEnter a name to choose: " << std::endl;
	char* chosen = getln();
	Player player;	

	std::ifstream ifile(db, std::ios::binary);
	while (!ifile.eof()) {
		ifile >> player;
		if (!strcmp(chosen, player.getName())) {
			m_player = player;
			delete[] chosen;
			return true;
		}
	}
	delete[] chosen;
	ifile.close();
	std::cout << "Could not find player with that name :( Try again" << std::endl;

	return false;
}

void Game::writeNewPlayersData()
{
	std::ofstream ofile(db, std::ios::binary | std::ios::app);
	if (ofile.is_open()) {
		unsigned len = m_player.getLen();
		char* name = m_player.getName();
		unsigned age = m_player.getAge();
		unsigned wins = m_player.getWins();
		double coeff = m_player.getCoeff();
		unsigned games = m_player.getNumOfGames();

		ofile.write((const char*)&len, sizeof(int));
		ofile.write(name, len*sizeof(char));
		ofile.write((const char*)&age, sizeof(unsigned));
		ofile.write((const char*)&wins, sizeof(unsigned));
		ofile.write((const char*)&coeff, sizeof(double));
		ofile.write((const char*)&games, sizeof(unsigned));

		ofile.close();
	}

}

void Game::getNewPlayersData()
{
	unsigned age;
	std::cout << "Enter player's name: ";
	std::cin.get();
	char* name = getln();
	std::cout << "Enter player's age: ";
	std::cin >> age;
	
	m_player.setName(name);
	m_player.setAge(age);

	delete[] name;
}

void Game::playerSetup()
{
	char input;
	int choice;
	std::cout << "Do you want to choose player from database(1) or create your own(2)?: ";

	while (true){
		std::cin >> input;
		if (input == '1' || input == '2') { // checking whether the input is valid
			choice = input - '0'; // if so convert the char input to int

			break;
		}

		std::cout << "Invalid input :( Try again" << std::endl;
	}

	if (choice == 1) {
		bool thereArePlayers = displayAllPlayersData(); //returns false if there aren't any players
		if (thereArePlayers) {
			std::cin.get();
			while (!choosePlayer()); // waiting for the player to enter a name, which is in the database
		}
		else {
			std::cout << "Couldn't find any players :( Please create your own" << std::endl;
			choice = 2;
		}
	}
	if (choice == 2) {
		getNewPlayersData();
		writeNewPlayersData();
	}
}

unsigned Game::evalPoints(Card const& card) // returns the point value of the given card
{
	unsigned card_points;

	switch (card.getRank()) {
	case Rank::Ace:
		if (m_player.getCurPoints() >= 11) card_points = 1;
		else card_points = 11;
		break;
	case Rank::Two:
		card_points = 2;
		break;
	case Rank::Three:
		card_points = 3;
		break;
	case Rank::Four:
		card_points = 4;
		break;
	case Rank::Five:
		card_points = 5;
		break;
	case Rank::Six:
		card_points = 6;
		break;
	case Rank::Seven:
		card_points = 7;
		break;
	case Rank::Eigth:
		card_points = 8;
		break;
	case Rank::Nine:
		card_points = 9;
		break;
	case Rank::Ten:
		card_points = 10;
		break;
	case Rank::J:
		card_points = 10;
		break;
	case Rank::Q:
		card_points = 10;
		break;
	case Rank::K:
		card_points = 10;
		break;
	default:
		card_points = 0;
	}

	return card_points;
}

void Game::calcCoeff(bool won)
{
	m_player.addGamePlayed();
	if (won) m_player.addWin();
		
	unsigned wins = m_player.getWins();
	unsigned games = m_player.getNumOfGames();

	m_player.setCoeff(wins / (double)games);
}

bool Game::hit()
{
	Card card = m_deck.draw();
	m_player.addPoints(evalPoints(card));
	std::cout << "You drew ";
	card.printCard();
	std::cout << ",  current score is: " << m_player.getCurPoints() << std::endl;
	if (m_player.getCurPoints() > (unsigned)21) return true;

	return false;
}

void Game::probs(Card const& first_card)
{
	int p = 0;
	double probability;
	if (m_player.getCurPoints() >= 10) {
		unsigned i = 0;
		for (; i < m_deck.getSize(); ++i) {
			if ((Card)first_card == m_deck[i]) break;
			if (21 - evalPoints(m_deck[i]) == m_player.getCurPoints()) p++;
		}
		probability = p / (double)i;
	}
	else probability = 0;

	std::cout << "Probability of getting 21 next round is : " << std::fixed << std::setprecision(3) << probability << std::endl;
}

bool Game::playerDraws()
{
	Card first_card = m_deck.draw();
	m_player.addPoints(evalPoints(first_card));
	std::cout << "You drew ";
	first_card.printCard();
	std::cout << ", current score is : " << m_player.getCurPoints() << std::endl;

	char move[12]; //strlen(Probability)
	bool busted = false;
	do {
		std::cout << "Hit/Stand/Probability" << std::endl;
		std::cin >> move;

		if (!strcmp(move, "Hit") || !strcmp(move, "hit") || !strcmp(move, "h")) busted = hit(); // returns true when the player busted
		else if (!strcmp(move, "Probability") || !strcmp(move, "probability") || !strcmp(move, "p")) probs(first_card);
		else if (!strcmp(move, "Stand") || !strcmp(move, "stand") || !strcmp(move, "s")) break;
	} while (!busted); //breaks when the player is busted

	return busted;
}

unsigned Game::dealerDraws()
{
	Card card;
	unsigned dealers_score = 0;
	std::cout << "\nThe dealer drew: ";
	do {
		card = m_deck.draw();
		dealers_score += evalPoints(card);
		card.printCard();
	} while (dealers_score < 17 && std::cout << ", ");
	std::cout << "\nDealer's score is: " << dealers_score << std::endl;

	return dealers_score;
}

void Game::begin()
{
	playerSetup();

	unsigned deck_size;
	std::cout << "You're playing as " << m_player.getName() << ". Choose a deck size, if you will: ";
	do {
		std::cin >> deck_size;
	} while (deck_size < 1);
	Deck custom_deck = Deck(deck_size); 
	m_deck = custom_deck;

	std::cout << "\nThe game has begun!" << std::endl;

	bool busted = playerDraws();
	if (busted) {
		std::cout << "You lose!";
		calcCoeff(false); // doesnt add win
	}
	else {

		unsigned dealers_points = dealerDraws();
		if (dealers_points > 21 || m_player.getCurPoints() >= dealers_points) {
			std::cout << "You win!" << std::endl;
			calcCoeff(true); // adds win
		}
		else {
			std::cout << "You lose!" << std::endl;
			calcCoeff(false); // doesnt add win	
		}
	}

	updatePlayers();
}
