/*
* Данный файл содержит инструменты взаимодействия с данными пользователя
*/

#ifndef _classes_h
#define _classes_h
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

const unsigned FULL_NAME_CATEGORY = 1;
const unsigned DATE_OF_BIRTH_CATEGORY = 2;
const unsigned COMPOUND_CATEGORY = 3;
const unsigned IS_IN_THE_TEAM_CATEGORY = 4;
const unsigned PARTICIPATION_IN_THE_LAST_MATCH_CATEGORY = 5;
const unsigned NUMBER_OF_YELLOW_CARDS_CATEGORY = 6;
const unsigned MAX_LENGTH_OF_DATE = 20;
const std::string CORE_TEAM = "Core member";
const std::string PARTICIPATE_IN_THE_LAST_MATCH = "Participated in the last match";
const unsigned NUMBER_OF_YELLOW_CARDS = 1;

class Player {
public:
	// Конструктор, не принимающий аргументов, создающий экземпляр класса со стандартными значениями
	// Имя игрока = 'Example', Дата рождения - 1 января 1900 года, Состав - дополнительный, 
	// Состоит в сборной - нет, Участие в последнем матче - нет, Кол-во желтых карточек - 0
	Player() { 
		playersName_ = "Example";
		dateOfBirth_.tm_year = 1900;
		dateOfBirth_.tm_mon = 0;
		dateOfBirth_.tm_mday = 1;
		compound_ = false;
		isInTheTeam_ = false;
		participationInTheLastMatch_ = false;
		numberOfYellowCards_ = 0;
	}

	// Конструктор, создающий экземпляр класса со значениями, переданными пользователем
	Player(std::string playersName, std::tm dateOfBirth, bool compound, bool isInTheTeam, bool participationInTheLastMatch,
		unsigned numberOfYellowCards) : playersName_(playersName), dateOfBirth_(dateOfBirth), compound_(compound),
		isInTheTeam_(isInTheTeam), participationInTheLastMatch_(participationInTheLastMatch), numberOfYellowCards_(numberOfYellowCards) {}

	// Конструктор копирования, служащий для создания объекта путем копирования элементов другого объекта
	Player(const Player& other) { 
		playersName_ = other.playersName_;
		dateOfBirth_ = other.dateOfBirth_;
		compound_ = other.compound_;
		isInTheTeam_ = other.isInTheTeam_;
		participationInTheLastMatch_ = other.participationInTheLastMatch_;
		numberOfYellowCards_ = other.numberOfYellowCards_;
	}

	// Деструктор, вызывается при уничтожении объекта
	~Player() {}

	// Перегрузка оператора <<, для шаблонизирования представления информации о полях класса
	friend std::ostream& operator<<(std::ostream& os, Player& other);

	// Перегрузка оператора >>, для универсального ввода информации, необходимой при создании класса
	friend std::istream& operator>>(std::istream& is, Player& other);

	// Метод для получения ФИО игрока
	std::string getPlayersName() {
		return playersName_;
	}

	// Метод для получения даты рождения игрока
	std::string getDateOfBirth() {
		char str[MAX_LENGTH_OF_DATE];

		if (std::strftime(str, sizeof(str), "%D", &dateOfBirth_)) {
			return str;
		}
		else {
			return "Unable to get date of birth";
		}
	}

	// Метод для получения информации о том, в основном составе или на скамейке запасных находится игрок
	std::string getCompound() {
		if (compound_) {
			return "Core member";
		}
		else {
			return "Bench member";
		}
	}

	// Метод для получения информации о том, состоит ли игрок в сборной или нет
	std::string getIsInTheTeam() {
		if (isInTheTeam_) {
			return "Member of the national team";
		}
		else {
			return "Not a member of the national team";
		}
	}

	// Метод для получения информации о том, участвовал ли игрок в последнем матче
	std::string getParticipationInTheLastMatch() {
		if (participationInTheLastMatch_) {
			return "Participated in the last match";
		}
		else {
			return "Didn't participated in the last match";
		}
	}

	// Метод для получения информации о кол-во желтых карточек игрока
	unsigned getNumberOfYellowCards() {
		return numberOfYellowCards_;
	}

	// Перегрузка оператора присваивания для возможности присваивания экземпляра класса
	Player& operator=(const Player& other) {
		if (this != &other) {
			playersName_ = other.playersName_;
			dateOfBirth_ = other.dateOfBirth_;
			compound_ = other.compound_;
			isInTheTeam_ = other.isInTheTeam_;
			participationInTheLastMatch_ = other.participationInTheLastMatch_;
			numberOfYellowCards_ = other.numberOfYellowCards_;
		}
		return *this;
	}

	// Перегрузка оператора равенства, для сравнения двух элементов типа Player
	bool operator==(const Player& other) {
		if (playersName_ == other.playersName_ && dateOfBirth_.tm_year == other.dateOfBirth_.tm_year &&
			dateOfBirth_.tm_mon == other.dateOfBirth_.tm_mon && dateOfBirth_.tm_mday == other.dateOfBirth_.tm_mday &&
			compound_ == other.compound_ && isInTheTeam_ == other.isInTheTeam_ &&
			participationInTheLastMatch_ == other.participationInTheLastMatch_ && numberOfYellowCards_ == other.numberOfYellowCards_) {
			return true;
		}
		else {
			return false;
		}
	}

private:
	std::string playersName_;
	std::tm dateOfBirth_{};
	bool compound_{};
	bool isInTheTeam_{};
	bool participationInTheLastMatch_{};
	unsigned numberOfYellowCards_{};
};

class PlayersList {
public:
	// Конструктор, создающий пустой контейнер для хранения объектов типа Player
	PlayersList() {}

	// Конструктор, создающий заполненный контейнер, на основе переданного
	PlayersList(std::vector<Player> players) {
		playersList_ = players;
	}

	// Деструктор, вызывается при уничтожении объекта
	~PlayersList() {}

	// Метод, служащий для добавления элементов, в конец контейнера
	// На вход принимает экземпляр типа Player, который необходимо добавить
	void add(const Player& player) {
		playersList_.push_back(player);
	}

	// Метод, служащий для удаления элемента, выбранного пользователем
	// На вход принимает номер элемента из списка, который необходимо удалить
	void remove(unsigned number) {
		if ((int)number <= (playersList_.end() - playersList_.begin())) {
			playersList_.erase(playersList_.begin() + number - 1);
		}
	}

	// Метод, служащий для сортировки одного из параметров класса Player, в зависимости от переданной функции сравнения
	// На вход принимает функцию сравнения для выбранного параметра
	void sort(bool (*cmp)(Player left, Player right)) {
		std::sort(playersList_.begin(), playersList_.end(), cmp);
	}

	// Метод, служащий для поиска переданного элемента, в выбранной категории.
	// На вход принимает параметр и значение, которое нужно найти
	// Возвращает список всех элементов, содержащих данное значение в выбранной категории
	// Категории: 1 - ФИО игрока, 2 - дата рождения, 3 - состав, 4 - состоит в сборной,
	// 5 - участие в последнем матче, 6 - кол-во желтых карточек
	std::vector<Player> find(unsigned parameter) {
		std::vector<Player> found;
		
		try
		{
			switch (parameter)
			{
			case FULL_NAME_CATEGORY:
			{
				std::string value;
				std::string blankShot;
				std::getline(std::cin, blankShot);
				std::getline(std::cin, value);
				std::for_each(playersList_.begin(), playersList_.end(), [&value, &found](Player& element) { if (element.getPlayersName() == value) { found.push_back(element); } });
				break;
			}
			case DATE_OF_BIRTH_CATEGORY:
			{
				std::string value;
				std::string blankShot;
				std::getline(std::cin, blankShot);
				std::getline(std::cin, value);
				std::for_each(playersList_.begin(), playersList_.end(), [&value, &found](Player& element) { if (element.getDateOfBirth() == value) { found.push_back(element); } });
				break;
			}
			case COMPOUND_CATEGORY:
			{
				std::string value;
				std::string blankShot;
				std::getline(std::cin, blankShot);
				std::getline(std::cin, value);
				std::for_each(playersList_.begin(), playersList_.end(), [&found, &value](Player& element) { if (element.getCompound() == value) { found.push_back(element); } });
				break;
			}
			case IS_IN_THE_TEAM_CATEGORY:
			{
				std::string value;
				std::string blankShot;
				std::getline(std::cin, blankShot);
				std::getline(std::cin, value);
				std::for_each(playersList_.begin(), playersList_.end(), [&value, &found](Player& element) { if (element.getIsInTheTeam() == value) { found.push_back(element); } });
				break;
			}
			case PARTICIPATION_IN_THE_LAST_MATCH_CATEGORY:
			{
				std::string value;
				std::string blankShot;
				std::getline(std::cin, blankShot);
				std::getline(std::cin, value);
				std::for_each(playersList_.begin(), playersList_.end(), [&value, &found](Player& element) { if (element.getParticipationInTheLastMatch() == value) { found.push_back(element); } });
				break;
			}
			case NUMBER_OF_YELLOW_CARDS_CATEGORY:
			{
				unsigned value;
				std::cin >> value;
				std::for_each(playersList_.begin(), playersList_.end(), [&value, &found](Player& element) { if (element.getNumberOfYellowCards() == value) { found.push_back(element); } });
				break;
			}
			default:
				break;
			}

		}
		catch (const std::exception&)
		{
			std::cout << "An error occurred while entering data" << std::endl;
		}
		return found;
	}	

	// Перегрузка оператора << для универсального вывода информации обо всех значениях списка
	friend std::ostream& operator<<(std::ostream& os, PlayersList& other);
	
	// Метод, позволяющий редактировать выбранного пользователя
	void edit(unsigned number, const Player& player) {
		if ((int)number <= playersList_.size()) {
			playersList_[number - 1] = player;
		}
	}

	// Метод, для получения списка, содержащего информацию обо всех игроках
	std::vector<Player> getPlayersList() {
		return playersList_;
	}

	// Метод для получения списка игроков, которые состоят в основном составе, участвовали в последней игре и имеют одну жёлтую карточку
	std::vector<Player> areInTheMainTeamParticipatedInTheLastGameAndHaveOneYellowCard() {
		std::vector<Player> found;

		std::for_each(playersList_.begin(), playersList_.end(), [&found](Player& element) { if (element.getCompound() == CORE_TEAM &&
			element.getParticipationInTheLastMatch() == PARTICIPATE_IN_THE_LAST_MATCH && element.getNumberOfYellowCards() == NUMBER_OF_YELLOW_CARDS) {
			found.push_back(element);
		} });
		return found;
	}

private:
	std::vector<Player> playersList_;
};

#endif // !_classes_h
