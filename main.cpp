// Module imports
import std;
import users;
import flights;
import payment;
import menus;

// Forward declarations for input validation
int getValidInt();
double getValidDouble();

int main() {
	loadFlights();
	loadAccounts();
	runMainMenu();
	return 0;
}

// Reads and validates integer input, returns -1 on invalid input
int getValidInt() {
	int choice;
	std::cin >> choice;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1;
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return choice;
}

// Reads and validates double input, returns -1.0 on invalid input
double getValidDouble() {
	double value{};
	std::cin >> value;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1.0;
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return value;
}