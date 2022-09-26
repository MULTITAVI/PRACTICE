#include "classes.h"
#include <limits>

const unsigned SHOW_ITEMS = 1;
const unsigned ADD_ITEM = 2;
const unsigned DELETE_ITEM = 3;
const unsigned SORTING = 4;
const unsigned SEARCH = 5;
const unsigned EDIT_ITEM = 6;
const unsigned CORE_TEAM_PARTICIPATED_IN_THE_LAST_MATCH_ONE_YELLOW_CARD = 7;
const unsigned EXIT = 8;
const unsigned SORTING_BY_NAME = 1;
const unsigned SORTING_BY_DATE_OF_BIRTH = 2;
const unsigned SORTING_BY_NUMBER_OF_YELLOW_CARDS = 3;
const unsigned ASCENDING = 1;
const unsigned DESCENDING = 2;
const unsigned YEAR_START_POS = 6;
const unsigned MONTH_START_POS = 0;
const unsigned DAY_START_POS = 3;
const unsigned LENGTH_TO_COMPARE = 2;

// Перегрузка оператора << для класса Player, которая выводит в консоль информацию об игроке табулированную друг от друга по два раза
std::ostream& operator<<(std::ostream& os, Player& other) {
	os << other.getPlayersName() << "\t\t" << other.getDateOfBirth() << "\t\t" <<
		other.getCompound() << "\t\t" << other.getIsInTheTeam() << "\t\t" <<
		other.getParticipationInTheLastMatch() << "\t\t" << other.getNumberOfYellowCards() << "\n";
	return os;
}

// Перегрузка оператора >> для класса Player, которая считывает информацию из консоли и присваивает контейнеру Player полученную информацию
std::istream& operator>>(std::istream& is, Player& other) {
	try
	{
		std::string blankShot;
		std::string playersName;
		std::tm dateOfBirth{};
		bool compound{};
		bool isInTheTeam{};
		bool participationInTheLastMatch{};
		unsigned numberOfYellowCards;

		unsigned mon;
		unsigned year;
		

		std::getline(is, blankShot);
		std::getline(is, playersName);
		is.exceptions(std::istream::failbit | std::istream::badbit);
		try
		{
			is >> dateOfBirth.tm_mday >> mon >> year;

			dateOfBirth.tm_mon = mon - 1;
			dateOfBirth.tm_year = year - 1900;

			is >> compound >> isInTheTeam >> participationInTheLastMatch >> numberOfYellowCards;

			Player player = Player(playersName, dateOfBirth, compound, isInTheTeam, participationInTheLastMatch, numberOfYellowCards);
			other = player;
		}
		catch (std::istream::failure e)
		{
			std::cout << "Failed to enter data" << std::endl;
			is.clear(); // на случай, если предыдущий ввод завершился с ошибкой
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		return is;
	}
	catch (const std::exception&)
	{
		std::cout << "An error occurred while entering data" << std::endl;
		return is;
	}
}

//  Перегрузка оператора << для класса PlayersList, которая выводит информацию обо всех игроках в виде таблицы
std::ostream& operator<<(std::ostream& os, PlayersList& playersList) {
	std::vector<Player> players = playersList.getPlayersList();
	unsigned step = 1;
	std::for_each(players.begin(), players.end(), [&os, &step](Player& element) { os << step++ << "\t\t" << element; });
	
	return os;
}

// Функция для сравнения строк в порядке возрастания
bool comparePlayersNameAscending(Player left, Player right) {
	return left.getPlayersName() < right.getPlayersName() ? true : false;
}

// Фунукция для сравнения строк в порядке убывания
bool comparePlayersNameDescending(Player left, Player right) {
	return left.getPlayersName() < right.getPlayersName() ? false : true;
}

// Функция для сравнения дат рождения в порядке возрастания
bool compareDateOfBirthAscending(Player left, Player right) {
	if (left.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE) < right.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE)) {
		return true;
	}
	else if(left.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE) == right.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE)
			&& left.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE) < right.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE)) {
		return true;
	}
	else if (left.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE) == right.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE)
			&& left.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE) == right.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE)
			&& left.getDateOfBirth().substr(DAY_START_POS, LENGTH_TO_COMPARE) < right.getDateOfBirth().substr(DAY_START_POS, LENGTH_TO_COMPARE)) {
		return true;
	}
	else {
		return false;
	}
}

// Функция для сравнения дат рождения в порядке убывания
bool compareDateOfBirthDescending(Player left, Player right) {
	if (left.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE) < right.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE)) {
		return false;
	}
	else if (left.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE) == right.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE)
			&& left.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE) < right.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE)) {
		return false;
	}
	else if (left.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE) == right.getDateOfBirth().substr(YEAR_START_POS, LENGTH_TO_COMPARE)
			&& left.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE) == right.getDateOfBirth().substr(MONTH_START_POS, LENGTH_TO_COMPARE)
			&& left.getDateOfBirth().substr(DAY_START_POS, LENGTH_TO_COMPARE) < right.getDateOfBirth().substr(DAY_START_POS, LENGTH_TO_COMPARE)) {
		return false;
	}
	else {
		return true;
	}
}

// Функция для сравнения кол-ва желтых карточек в порядке возрастания
bool compareNumberOfYellowCardsAscending(Player left, Player right) {
	return left.getNumberOfYellowCards() < right.getNumberOfYellowCards() ? true : false;
}

// Функция для сравнения кол-ва желтых карточек в порядке убывания
bool compareNumberOfYellowCardsDescending(Player left, Player right) {
	return left.getNumberOfYellowCards() < right.getNumberOfYellowCards() ? false : true;
}

// Функция, отвечающая за показ приветственного меню
void welcomeMenu() {
	std::cout << "Welcome to the player data software" << std::endl;
}

// Функция, отвечающая за показ базовых действий
void basicActionsMenu() { 
	std::cout << "Choose one of the actions:" << std::endl <<
		"1. Show items" << std::endl << "2. Add item" << std::endl <<
		"3. Delete item" << std::endl << "4. Sorting" << std::endl <<
		"5. Search" << std::endl << "6. Edit item" << std::endl <<
		"7. Find first team players who participated in the last match and have one yellow card" << std::endl <<
		"8. Exit the program" << std::endl;
}

// Функция, показывающая памятку о том, как правильно вводить данные
void informationAboutCorrectDataEntry() {
	std::cout << "To enter the data correctly, follow the following example:" << std::endl <<
		"The first line is the player's full name, then three numbers are responsible for the day, month and year of the player's birth" << std::endl <<
		"Further, the number 1 or 0, where 1 means the player of the main team, 0 means the player on the bench" << std::endl <<
		"Similarly with the next number, 1 - is a member of the team, 0 - is not a member" << std::endl <<
		"Then again 1 or 0, 1 - participated in the last match, 0 - did not participate" << std::endl <<
		"The last number is the number of yellow cards" << std::endl;
}

// Функция, показывающее меню категорий, доступных для сортировки
void menuWithCategoriesWhenSorting() {
	std::cout << "Select the category you want to sort by:" << std::endl <<
		"1. Sorting by name" << std::endl <<
		"2. Sorting by date of birth" << std::endl <<
		"3. Sorting by number of yellow cards" << std::endl;
}

// Функция, показывающее меню сортировки с выбором возрастания или убывания
void descendingAscendingMenu() {
	std::cout << "Select sort type:" << std::endl <<
		"1. Ascending" << std::endl <<
		"2. Descending" << std::endl;
}

// Функция, показывающая шаблонный текст о найденных элементах
void informationAboutWhatWasFound() {
	std::cout << "Found the following items:" << std::endl;
}

// Функция, показывающая меню с категориями для поиска
void menuWithCategoriesWhenSearching() {
	std::cout << "Select a category to search:" << std::endl <<
		"1. Player's name" << std::endl <<
		"2. Player's date of birth" << std::endl <<
		"3. Main squad or bench" << std::endl <<
		"4. Member of the national team or not" << std::endl <<
		"5. Participated in the last match or not" << std::endl <<
		"6. Number of yellow cards" << std::endl;
}

// функция, показывающая информацию о верном вводе данных для поиска
void informationAboutSearch() {
	std::cout << "Enter the value you want to find" << std::endl <<
		"Full name - string" << std::endl <<
		"Date of birth - format string 'mm/dd/yy'" << std::endl <<
		"Compound - 'Core member' or 'Bench member'" << std::endl <<
		"Member of the national team - 'Member of the national team' or 'Not a member of the national team'" << std::endl <<
		"Participation in the last match - 'Participated in the last match' or 'Didn't participated in the last match'" << std::endl <<
		"For the number oof yellow cards, enter a number" << std::endl;
}

int main() {
	welcomeMenu();
	
	unsigned choice;
	PlayersList playersList = PlayersList();

	while (true) {
		basicActionsMenu();

		std::cin.exceptions(std::istream::failbit | std::istream::badbit);
		try
		{
			std::cin >> choice;
		}
		catch (std::istream::failure e)
		{
			std::cout << "Failed to enter data" << std::endl;
			std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		switch (choice)
		{
		case SHOW_ITEMS:
		{
			std::cout << playersList;
			break;
		}
		case ADD_ITEM:
		{
			informationAboutCorrectDataEntry();
			Player player = Player();
			Player blankShot = Player();
			std::cin >> player;
			if (player == blankShot) {
				break;
			}
			playersList.add(player);
			break;
		}
		case DELETE_ITEM:
		{
			std::cout << playersList;
			std::cout << "Enter the	number of the element to be removed:" << std::endl;
			unsigned numberOfTheElementToBeRemoved;
			std::cin.exceptions(std::istream::failbit | std::istream::badbit);
			try
			{
				std::cin >> numberOfTheElementToBeRemoved;
				playersList.remove(numberOfTheElementToBeRemoved);
			}
			catch (std::istream::failure e)
			{
				std::cout << "Failed to enter data" << std::endl;
				std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			break;
		}
		case SORTING:
		{
			menuWithCategoriesWhenSorting();
			unsigned choosenCategory;
			unsigned ascendingOrDescending;
			std::cin.exceptions(std::istream::failbit | std::istream::badbit);
			try
			{
				std::cin >> choosenCategory;
			}
			catch (std::istream::failure e)
			{
				std::cout << "Failed to enter data" << std::endl;
				std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (choosenCategory)
			{
			case SORTING_BY_NAME:
			{
				descendingAscendingMenu();
				std::cin.exceptions(std::istream::failbit | std::istream::badbit);
				try
				{
					std::cin >> ascendingOrDescending;
				}
				catch (std::istream::failure e)
				{
					std::cout << "Failed to enter data" << std::endl;
					std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				switch (ascendingOrDescending)
				{
				case ASCENDING:
				{
					playersList.sort(comparePlayersNameAscending);
					break;
				}
				case DESCENDING:
				{
					playersList.sort(comparePlayersNameDescending);
					break;
				}
				default:
				{
					std::cout << "Incorrect data entered" << std::endl;
					break;
				}
				}
				break;
			}
			case SORTING_BY_DATE_OF_BIRTH:
			{
				descendingAscendingMenu();
				std::cin.exceptions(std::istream::failbit | std::istream::badbit);
				try
				{
					std::cin >> ascendingOrDescending;
				}
				catch (std::istream::failure e)
				{
					std::cout << "Failed to enter data" << std::endl;
					std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				switch (ascendingOrDescending)
				{
				case ASCENDING:
				{
					playersList.sort(compareDateOfBirthAscending);
					break;
				}
				case DESCENDING:
				{
					playersList.sort(compareDateOfBirthDescending);
					break;
				}
				default:
				{
					std::cout << "Incorrect data entered" << std::endl;
					break;
				}
				}
				break;
			}
			case SORTING_BY_NUMBER_OF_YELLOW_CARDS:
			{
				descendingAscendingMenu();
				std::cin.exceptions(std::istream::failbit | std::istream::badbit);
				try
				{
					std::cin >> ascendingOrDescending;
				}
				catch (std::istream::failure e)
				{
					std::cout << "Failed to enter data" << std::endl;
					std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				switch (ascendingOrDescending)
				{
				case ASCENDING:
				{
					playersList.sort(compareNumberOfYellowCardsAscending);
					break;
				}
				case DESCENDING:
				{
					playersList.sort(compareNumberOfYellowCardsDescending);
					break;
				}
				default:
				{
					std::cout << "Incorrect data entered" << std::endl;
					break;
				}
				}
				break;
			}
			default:
			{
				std::cout << "Incorrect data entered" << std::endl;
				break;
			}
			}
			break;
		}
		case SEARCH:
		{
			menuWithCategoriesWhenSearching();
			unsigned choosenCategory;
			std::cin.exceptions(std::istream::failbit | std::istream::badbit);
			try
			{
				std::cin >> choosenCategory;
				informationAboutSearch();
				std::vector<Player> data = playersList.find(choosenCategory);
				PlayersList foundData = PlayersList(data);
				informationAboutWhatWasFound();
				std::cout << foundData;
			}
			catch (std::istream::failure e)
			{
				std::cout << "Failed to enter data" << std::endl;
				std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			break;
		}
		case EDIT_ITEM:
		{
			std::cout << playersList;
			std::cout << "Enter the number of the element you want to edit" << std::endl;
			unsigned elementToEdit;
			std::cin.exceptions(std::istream::failbit | std::istream::badbit);
			try
			{
				std::cin >> elementToEdit;
				if (elementToEdit > playersList.getPlayersList().size()) {
					break;
				}
				Player player = Player();
				Player blankShot = Player();
				informationAboutCorrectDataEntry();
				std::cin >> player;
				if (player == blankShot) {
					break;
				}
				playersList.edit(elementToEdit, player);
			}
			catch (std::istream::failure e)
			{
				std::cout << "Failed to enter data" << std::endl;
				std::cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			break;
		}
		case CORE_TEAM_PARTICIPATED_IN_THE_LAST_MATCH_ONE_YELLOW_CARD:
		{
			std::vector<Player> data = playersList.areInTheMainTeamParticipatedInTheLastGameAndHaveOneYellowCard();
			PlayersList foundData = PlayersList(data);
			informationAboutWhatWasFound();
			std::cout << foundData;
			break;
		}
		case EXIT:
		{
			break;
		}
		default:
		{	
			std::cout << "Incorrect data entered" << std::endl;
			break;
		}
		}

		if (choice == EXIT) {
			break;
		}
	}

	return 0;
}			