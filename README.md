# Flight Reservation System (C++20 Modules)

## Overview

The Flight Reservation System is a command-line interface (CLI) application developed using modern C++ (C++20 modules). It simulates core airline operations such as user management, seat reservation, and payment processing.

The system is designed with a strong emphasis on modularity, separation of concerns, and maintainability, making it suitable for learning software architecture principles and foundational system design.

It also includes a secure authentication layer using Argon2id password hashing to ensure industry-standard password protection.

---

## Features

- Structured user management system
- Secure authentication with Argon2id password hashing
- Seat reservation and real-time availability tracking
- Payment initialization and verification workflow
- Interactive menu-driven CLI interface
- Modular architecture using C++20 modules (.ixx)
- Automated build process via batch script

---

## Project Architecture (Modular Breakdown)

### 1. Users Module (User Management)

Responsible for handling passenger-related data and identity management.

Responsibilities:
- Store and manage user information
- Handle user creation and validation
- Maintain unique user identification
- Integrate secure password verification

---

### 2. Seats Module (Reservation System)

Implements core seat booking and allocation logic.

Responsibilities:
- Track seat availability in real time
- Assign seats during reservation
- Prevent duplicate or conflicting bookings

---

### 3. Payment Module (Transaction Processing)

Encapsulates payment workflow and transaction verification.

Responsibilities:
- Initialize payment requests
- Verify transaction status
- Store and manage payment references

---

### 4. Menus Module (Interface Layer)

Acts as the interaction layer between user and system.

Responsibilities:
- Display system menus
- Capture and validate user input
- Route commands to appropriate modules

---

### 5. Crypto Module (Security Layer)

Implements secure password hashing using Argon2id.

Responsibilities:
- Hash passwords using Argon2id
- Verify password correctness securely
- Generate cryptographic salts
- Prevent plaintext password storage

---

## Security Implementation: Argon2id Password Hashing

### Overview

The system uses Argon2id, an industry-standard password hashing algorithm, to securely store user credentials. Plaintext password storage has been completely removed.

---

### Argon2id Configuration

- Algorithm: Argon2id
- Time Cost: 2 iterations
- Memory Cost: 2^19 KiB (~512 MiB)
- Parallelism: 1 thread
- Hash Output: 128 bytes (256 hex characters)

## Security Features

- Constant-time password comparison (prevents timing attacks)
- Unique salt per password (prevents rainbow table attacks)
- Memory-hard hashing (resists GPU/ASIC brute force attacks)
- Computationally expensive hashing (slows brute-force attempts)
- No plaintext password storage anywhere in the system
- Automatic migration from legacy password format

--- 

## Dependencies

- argon2 (via vcpkg)
  vcpkg install argon2:x64-windows
- nlohmann/json (for data serialization)
- curl (via vcpkg)
  vcpkg install curl
- C++20 modules support

---
## Build System

The project includes an automated build script (build.bat) for Windows which workd if MSVC compiler is already installed.

MSVC Build Command:
cl /std:c++latest /EHsc /nologo /W4 /MTd /Fe:app.exe *.ixx

Quick Build:
build\build.bat

---

## Usage

1. Compile the project using the build script or MSVC command
2. Replace the paystack public key in config\paystack_secret.txt with your actual secret key
3. Run the generated executable
4. Interact via the CLI menu
5. Perform operations such as:
   - User management
   - Seat booking
   - Payment processing

---

## How It Works

1. System initializes all modules at startup
2. User interacts via CLI menu
3. Input is routed to relevant module
4. Each module processes independently
5. Results are displayed back to the user

---

## Design Principles

- Modular architecture using C++20 modules
- Separation of concerns across system components
- Encapsulation of business logic
- Scalable structure for future expansion
- Secure authentication system integrated at core level

---

## Future Improvements

- Persistent database integration
- GUI version of the system
- Advanced seat selection visualization
- Multi-flight scheduling system
- Rate limiting for login attempts
- Two-factor authentication (2FA)
- Password reset via email verification
- Audit logging for authentication events

---

## Author

Gerald Mathew
“The Programmer — Flight Reservation System”

---

## License

This project is intended for educational and experimental purposes and may be extended or modified over time.
