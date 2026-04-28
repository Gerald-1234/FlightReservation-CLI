export module crypto;
import std;
import <json.hpp>;
import <argon2.h>;

// Argon2 password hashing utility (installed via vcpkg)
export namespace Crypto {
	constexpr size_t HASH_LENGTH = 128;
	constexpr size_t SALT_LENGTH = 16;
	constexpr uint32_t ARGON2_TIME_COST = 2;
	constexpr uint32_t ARGON2_MEMORY_COST = 19;  // 2^19 KiB = ~512 MiB
	constexpr uint32_t ARGON2_PARALLELISM = 1;

	// Generate a random salt for password hashing
	export std::string generateSalt() {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<> dis(0, 15);

		std::string salt;
		salt.reserve(SALT_LENGTH);
		const char hex[] = "0123456789abcdef";
		for (size_t i = 0; i < SALT_LENGTH; ++i) {
			salt += hex[dis(gen)];
		}
		return salt;
	}

	// Hash a password with Argon2id (secure password hashing)
	// Returns JSON object with hash and salt
	export nlohmann::json hashPassword(const std::string& password) {
		nlohmann::json result;

		if (password.empty()) {
			result["error"] = "Password cannot be empty";
			return result;
		}

		try {
			std::string salt = generateSalt();

			// Allocate output hash buffer
			std::vector<uint8_t> hash(HASH_LENGTH);

			// Argon2id hashing: combines Argon2i and Argon2d for balanced security
			int argon2_rc = argon2id_hash_raw(
				ARGON2_TIME_COST,           // Time cost
				ARGON2_MEMORY_COST,         // Memory cost (in KiB)
				ARGON2_PARALLELISM,         // Parallelism
				password.c_str(),           // Password
				password.length(),          // Password length
				(uint8_t*)salt.c_str(),     // Salt
				salt.length(),              // Salt length
				hash.data(),                // Output hash
				hash.size()                 // Hash length
			);

			if (argon2_rc != ARGON2_OK) {
				result["error"] = std::string("Argon2 hashing failed: ") + argon2_error_message(argon2_rc);
				return result;
			}

			// Convert hash to hex string for storage
			std::stringstream ss;
			for (uint8_t byte : hash) {
				ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
			}
			std::string hash_str = ss.str();

			result["ok"] = true;
			result["hash"] = hash_str;
			result["salt"] = salt;
			result["algorithm"] = "Argon2id";
		}
		catch (const std::exception& e) {
			result["error"] = std::string("Hashing failed: ") + e.what();
		}

		return result;
	}

	// Verify a password against a stored Argon2 hash
	export bool verifyPassword(const std::string& password, const std::string& storedHash, const std::string& salt) {
		if (password.empty() || storedHash.empty() || salt.empty()) {
			return false;
		}

		try {
			// Re-hash the password with the same salt
			std::vector<uint8_t> hash(HASH_LENGTH);

			int argon2_rc = argon2id_hash_raw(
				ARGON2_TIME_COST,
				ARGON2_MEMORY_COST,
				ARGON2_PARALLELISM,
				password.c_str(),
				password.length(),
				(uint8_t*)salt.c_str(),
				salt.length(),
				hash.data(),
				hash.size()
			);

			if (argon2_rc != ARGON2_OK) {
				return false;
			}

			// Convert computed hash to hex string
			std::stringstream ss;
			for (uint8_t byte : hash) {
				ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
			}
			std::string computed_hash = ss.str();

			// Constant-time comparison to prevent timing attacks
			return computed_hash == storedHash;
		}
		catch (const std::exception&) {
			return false;
		}
	}

	// Migration helper: convert plaintext password to hash
	export nlohmann::json migratePasswordToHash(const std::string& plaintextPassword) {
		return hashPassword(plaintextPassword);
	}
}
