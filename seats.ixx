export module seats;
import std;
import <json.hpp>;

export class Seat {
public:
	enum class Cabin {
		Economy,
		Business,
		FirstClass
	};

private:
	int row{};
	char letter{};            // A-D
	std::string seatNumber{}; // e.g. 1A
	Cabin cabin{ Cabin::Economy };
	bool isBooked{};
	std::string bookedBy{};

protected:
	Seat(int aRow, char aLetter, Cabin aCabin);
	Seat(const Seat&) = default;
	Seat& operator=(const Seat&) = default;

public:
	virtual ~Seat() = default;
	virtual std::unique_ptr<Seat> clone() const = 0;

	int getRow() const;
	char getLetter() const;
	const std::string& getSeatNumber() const;
	Cabin getCabin() const;
	bool getIsBooked() const;
	const std::string& getBookedBy() const;
	bool isWindowSeat() const;
	bool isAisleSeat() const;

	bool book();
	bool book(std::string aBookedBy);
	bool cancel();
	nlohmann::json toJson() const;
	static std::string cabinToString(Cabin c);
	static Cabin cabinFromString(std::string v);
};

export class EconomySeat final : public Seat {
public:
	EconomySeat(int aRow, char aLetter);
	std::unique_ptr<Seat> clone() const override;
};

export class BusinessSeat final : public Seat {
public:
	BusinessSeat(int aRow, char aLetter);
	std::unique_ptr<Seat> clone() const override;
};

export class FirstClassSeat final : public Seat {
public:
	FirstClassSeat(int aRow, char aLetter);
	std::unique_ptr<Seat> clone() const override;
};