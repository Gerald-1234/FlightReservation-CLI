export module crypto;
import std;
import "../include/json.hpp";
import "../include/argon2.h";

// Argon2 password hashing utility (installed via vcpkg)
export namespace Crypto {
	constexpr size_t HASH_LENGTH = 128;
	constexpr uint8_t SALT_LENGTH = 16;
	constexpr uint8_t ARGON2_TIME_COST = 2;
	constexpr uint8_t ARGON2_MEMORY_COST = 19;  // 2^19 KiB = ~512 MiB
	constexpr uint8_t ARGON2_PARALLELISM = 1;

	export std::string generateSalt(); // Generate a random salt for password hashing
	export nlohmann::json hashPassword(const std::string& password); // Returns JSON object with hash and salt
	export bool verifyPassword(const std::string& password, const std::string& storedHash, const std::string& salt); // Verify a password against a stored Argon2 hash
}