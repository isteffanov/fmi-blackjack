#include "Player.hpp"

Player::Player(const char* name, unsigned years, unsigned wins, double win_coeff, unsigned total_games)
{
	if (years < 18 || years > 90) std::cout << "Invalid years entered for player " << name << "!" << std::endl;
	else 
		init(name, years, wins, win_coeff, total_games);
}

Player::Player(Player const& other)
{
	if (this != &other) 
		init(other.m_name, other.m_years, other.m_wins, other.m_win_coeff, other.m_total_games);
	
}

Player& Player::operator=(Player const& other)
{
	if (this != &other) {
		delete[] m_name;
		init(other.m_name, other.m_years, other.m_wins, other.m_win_coeff, other.m_total_games);
	}

	return *this;
}

Player::~Player()
{
	delete[] m_name;
	m_namelen = 0;
}

void Player::init(const char* name, unsigned years, unsigned wins, double win_coeff, unsigned total_games)
{
	m_namelen = strlen(name);
	m_name = new char[m_namelen + 1];
	strcpy(m_name, name);

	m_years = years;
	m_wins = wins;
	m_win_coeff = win_coeff;
	m_cur_points = 0;
	m_total_games = total_games;
}

unsigned Player::getLen() const
{
	return m_namelen;
}

char* Player::getName() const
{
	return m_name;
}

unsigned Player::getAge() const
{
	return m_years;
}

unsigned Player::getCurPoints() const
{
	return m_cur_points;
}

unsigned Player::getWins() const
{
	return m_wins;
}

double Player::getCoeff() const
{
	return m_win_coeff;
}

unsigned Player::getNumOfGames() const
{
	return m_total_games;
}

void Player::setName(const char* name)
{
	delete[] m_name;
	m_namelen = strlen(name);
	m_name = new char[m_namelen + 1];
	strcpy(m_name, name);
}

void Player::setAge(unsigned age)
{
	if (age >= 18) m_years = age;
	else std::cout << "Invalid age!" << std::endl;
}

void Player::setCurPoints(unsigned points)
{
	m_cur_points = points;
}

void Player::setCoeff(double coeff)
{
	m_win_coeff = coeff;
}

bool Player::operator==(Player const& other)
{
	return (!strcmp(m_name, other.m_name) && m_years == other.m_years);
}

unsigned Player::findEditPosInFile(const char* file)
{
	std::ifstream ifile(file, std::ios::binary);
	while (!ifile.eof()) {
		int len;
		ifile.read((char*)&len, sizeof(int));

		char* name = new char[len + 1];
		if (name) {
			ifile.read(name, len);
			name[len] = '\0';
		}

		unsigned age;
		ifile.read((char*)&age, sizeof(unsigned)); // ^ get the length of the name, the name itself and the age

		if (!strcmp(m_name, name)) {			  //if the name in the file matches the objects name
			unsigned pos = ifile.tellg();		  //the position of the file pointer is returned
			ifile.close();
			return pos;
		}
												//otherwise the other data is skipped through and we proceed to the next player in database	
		unsigned wins;
		ifile.read((char*)&wins, sizeof(unsigned));
		double coeff;
		ifile.read((char*)&coeff, sizeof(double));
		unsigned games;
		ifile.read((char*)&games, sizeof(unsigned));

		delete[] name;
	}
}

void Player::printPlayer() const
{
	std::cout << m_name << ", " << m_years << " years old, has " << m_wins << " total wins with "
				<< std::fixed << std::setprecision(3) << m_win_coeff << " winning coefficient" << std::endl;
}

unsigned Player::addPoints(unsigned points)
{
	return (m_cur_points += points);
}

void Player::addWin()
{
	m_wins += 1;
}

void Player::addGamePlayed()
{
	m_total_games += 1;
}

std::ifstream& operator>>(std::ifstream& stream, Player& player)
{
	unsigned len = 0;
	stream.read((char*)&len, sizeof(int));

	char* name = new char[len + 1];
	if (name) {
		stream.read(name, len * sizeof(char));
		name[len] = '\0';
	}
	player.setName(name);
	
	stream.read((char*)&player.m_years, sizeof(unsigned));
	stream.read((char*)&player.m_wins, sizeof(unsigned));
	stream.read((char*)&player.m_win_coeff, sizeof(double));
	stream.read((char*)&player.m_total_games, sizeof(unsigned));

	delete[] name;

	return stream;
}

std::fstream& operator>>(std::fstream& stream, Player& player)
{
	unsigned len = 0;
	stream.read((char*)&len, sizeof(int));

	char* name = new char[len + 1];
	if (name) {
		stream.read(name, len * sizeof(char));
		name[len] = '\0';
	}
	player.setName(name);

	stream.read((char*)&player.m_years, sizeof(unsigned));
	stream.read((char*)&player.m_wins, sizeof(unsigned));
	stream.read((char*)&player.m_win_coeff, sizeof(double));
	stream.read((char*)&player.m_total_games, sizeof(unsigned));

	delete[] name;

	return stream;
}
