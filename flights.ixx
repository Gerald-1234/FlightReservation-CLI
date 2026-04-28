export module flights;
import std;
import <json.hpp>;
export import seats;

const std::unordered_map<std::string, std::string> airports = {
	// Airport codes and their corresponding names
	{"LOS", "Murtala Muhammed International Airport, Lagos"},
	{"ABV", "Nnamdi Azikiwe International Airport, Abuja"},
	{"PHC", "Port Harcourt International Airport"},
	{"KAN", "Mallam Aminu Kano International Airport"},
	{"ENU", "Akanu Ibiam International Airport, Enugu"},
	{"ILR", "Ilorin International Airport"},
	{"JOS", "Yakubu Gowon Airport, Jos"},
	{"CBQ", "Margaret Ekpo International Airport, Calabar"},
	{"BEN", "Benin Airport"},
	{"QOW", "Sam Mbakwe Airport, Owerri"},
	{"AKR", "Akure Airport"},
	{"YOL", "Yola Airport"},
	{"IBA", "Ibadan Airport"},
	{"MDI", "Makurdi Airport"},
	{"SKO", "Sadiq Abubakar III International Airport, Sokoto"},
	{"MIU", "Maiduguri International Airport"},
	{"ZAR", "Zaria Airport"},
	{"GMO", "Gombe Lawanti International Airport"},
	{"DUT", "Dutse International Airport"},
	{"KAD", "Kaduna Airport"},
	{"ABB", "Asaba International Airport"}
};

export class Flight {
public:
	enum class Status {
		Scheduled,
		Boarding,
		Departed,
		Delayed,
		Cancelled
	};

	static constexpr int DefaultSeats = 200;
	static constexpr int MaxSeats = 500;

private:
	std::string id{};
	std::string airline{};
	std::string origin{};
	std::string destination{};
	std::string departureTime{}; // YYYY-MM-DD HH:MM
	std::string arrivalTime{};   // YYYY-MM-DD HH:MM
	std::string terminal{};
	std::string gate{};
	int totalSeats{};
	int availableSeats{};
	double ticketPrice{};
	Status status{ Status::Scheduled };
	std::vector<std::unique_ptr<Seat>> seats{};

	static std::unique_ptr<Seat> makeSeatForRow(int row, char letter);
	void initializeSeats(int seatCount);
	static std::unique_ptr<Seat> seatFromJson(const nlohmann::json& js);
	static std::string statusToString(Status s);
	static Status statusFromString(std::string v);
	static bool isValidAirportCode(const std::string& code);
	static bool isValidDateTimeFormat(const std::string& dateTime);

public:
	Flight();

	Flight(const Flight& other);
	Flight& operator=(const Flight& other);

	Flight(std::string aId, std::string anAirline, std::string anOrigin, std::string aDestination, std::string aDepartureTime, std::string anArrivalTime, int aTotalSeats, double aTicketPrice);

	// Setters
	bool setId(std::string aId);
	bool setAirline(std::string anAirline);
	bool setOrigin(std::string anOrigin);
	bool setDestination(std::string aDestination);
	bool setDepartureTime(std::string aDepartureTime);
	bool setArrivalTime(std::string anArrivalTime);
	bool setTotalSeats(int aTotalSeats);
	bool setTicketPrice(double aTicketPrice);

	void setTerminal(std::string aTerminal);
	void setGate(std::string aGate);
	void setStatus(Status aStatus);

	// Getters
	const std::string& getId() const;
	const std::string& getAirline() const;
	const std::string& getOrigin() const;
	const std::string& getDestination() const;
	const std::string& getDepartureTime() const;
	const std::string& getArrivalTime() const;
	const std::string& getTerminal() const;
	const std::string& getGate() const;
	int getTotalSeats() const;
	int getAvailableSeats() const;
	double getTicketPrice() const;
	Status getStatus() const;

	int getBookedSeats() const;
	bool hasAvailableSeats(int seatsRequested = 1) const;
	Seat* findSeat(const std::string& seatNumber);
	const std::vector<std::unique_ptr<Seat>>& getSeats() const;
	nlohmann::json toJson() const;
	static Flight fromJson(const nlohmann::json& js);
	bool bookSeat(const std::string& seatNumber);
	bool cancelSeat(const std::string& seatNumber);
	bool bookSeats(int seatCount = 1);
	bool cancelSeats(int seatCount = 1);
};

export inline std::unordered_map<std::string, Flight> flights;

export void saveFlights(const std::unordered_map<std::string, Flight>& flightCategory);
export void loadFlights(std::unordered_map<std::string, Flight>& flightCategory);
export void saveFlights();
export void loadFlights();