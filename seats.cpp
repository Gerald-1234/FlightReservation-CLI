module seats;

Seat::Seat(int aRow, char aLetter, Cabin aCabin) : row(aRow), letter(aLetter), seatNumber(std::to_string(aRow) + aLetter), cabin(aCabin) {}

int Seat::getRow() const { return row; }
char Seat::getLetter() const { return letter; }
const std::string& Seat::getSeatNumber() const { return seatNumber; }
Seat::Cabin Seat::getCabin() const { return cabin; }
bool Seat::getIsBooked() const { return isBooked; }
const std::string& Seat::getBookedBy() const { return bookedBy; }
bool Seat::isWindowSeat() const { return letter == 'A' || letter == 'D'; }
bool Seat::isAisleSeat() const { return letter == 'B' || letter == 'C'; }

bool Seat::book() {
	if (isBooked) return false;
	isBooked = true;
	bookedBy.clear();
	return true;
}

bool Seat::book(std::string aBookedBy) {
	if (!book()) return false;
	bookedBy = std::move(aBookedBy);
	return true;
}

bool Seat::cancel() {
	if (!isBooked) return false;
	isBooked = false;
	bookedBy.clear();
	return true;
}

nlohmann::json Seat::toJson() const {
	return {
		{ "Seat Number", seatNumber },
		{ "Cabin", cabinToString(cabin) },
		{ "Is Booked", isBooked },
		{ "Booked By", bookedBy }
	};
}

std::string Seat::cabinToString(Seat::Cabin c) {
	// Cabin enum to string converter: maps pricing tiers to display names
	if (c == Seat::Cabin::Economy) return "Economy";
	if (c == Seat::Cabin::Business) return "Business";
	if (c == Seat::Cabin::FirstClass) return "FirstClass";
	return "Economy";
}

Seat::Cabin Seat::cabinFromString(std::string v) {
	// String to cabin enum converter: case-insensitive, defaults to Economy
	std::transform(v.begin(), v.end(), v.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
	if (v == "BUSINESS") return Seat::Cabin::Business;
	if (v == "FIRSTCLASS" || v == "FIRST") return Seat::Cabin::FirstClass;
	return Seat::Cabin::Economy;
}

EconomySeat::EconomySeat(int aRow, char aLetter) : Seat(aRow, aLetter, Cabin::Economy) {}
// Polymorphic clone: creates heap-allocated copy via unique_ptr for safe polymorphic usage
std::unique_ptr<Seat> EconomySeat::clone() const { return std::make_unique<EconomySeat>(*this); }

BusinessSeat::BusinessSeat(int aRow, char aLetter) : Seat(aRow, aLetter, Cabin::Business) {}
// Polymorphic clone: creates heap-allocated copy via unique_ptr for safe polymorphic usage
std::unique_ptr<Seat> BusinessSeat::clone() const { return std::make_unique<BusinessSeat>(*this); }

FirstClassSeat::FirstClassSeat(int aRow, char aLetter) : Seat(aRow, aLetter, Cabin::FirstClass) {}
// Polymorphic clone: creates heap-allocated copy via unique_ptr for safe polymorphic usage
std::unique_ptr<Seat> FirstClassSeat::clone() const { return std::make_unique<FirstClassSeat>(*this); }