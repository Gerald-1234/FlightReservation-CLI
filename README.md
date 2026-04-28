# Flight Reservation System (C++ Modules)

A Command Line Interface (CLI) flight reservation system developed using modern C++ (C++20 modules). The project is structured with a strong focus on modularity, separation of concerns, and maintainability.

It simulates key airline operations such as user management, seat reservation, and payment processing, providing a clean and scalable architecture suitable for learning and real-world system design foundations.

Features
--------

- Structured user management system
- Seat reservation and availability tracking
- Payment initialization and verification workflow
- Interactive menu-driven CLI interface
- Modular architecture using C++20 modules (.ixx)
- Automated build process via batch script

Project Architecture (Modular Breakdown)
----------------------------------------

1. Users Module (User Management)

Responsible for handling all passenger-related data and identity management.

Key Responsibilities
- Store and manage user information
- Handle user creation and validation
- Maintain unique user identification

2. Seats Module (Reservation System)

Implements the core seat booking and allocation logic.

Key Responsibilities
- Track seat availability in real time
- Assign seats during reservation
- Prevent duplicate or conflicting bookings

3. Payment Module (Transaction Processing)

Encapsulates the payment workflow and transaction verification logic.

Key Responsibilities
- Initialize payment requests
- Verify transaction status
- Store and manage payment references

4. Menus Module (Interface Layer)

Acts as the interaction layer between the user and the system.

Key Responsibilities
- Display system menus
- Capture and validate user input
- Route commands to appropriate modules

Build System
------------

The project includes a build script (build.bat) to simplify compilation using a compatible C++ compiler.


Compilation Guide
-----------------

Compile from the root directory of the project.

MSVC (Recommended):
cl /std:c++latest /EHsc /nologo /W4 /MTd /Fe:app.exe *.ixx

Quick Build:

Alternatively, run:
build.bat

Usage
-----

1. Compile the project using the provided instructions
2. Run the generated executable
3. Interact with the system through the CLI menu
4. Perform operations such as:
   - Managing users
   - Booking and managing seats
   - Processing payments

How It Works
------------

1. The system initializes all modules at startup
2. The user interacts through a menu-driven CLI interface
3. Inputs are processed and routed to the relevant module
4. Each module handles its specific responsibility independently
5. Results are returned and displayed to the user

Design Principles
-----------------

- Modular design using C++20 modules for improved code organization
- Clear separation of concerns across system components
- Encapsulation of logic within dedicated modules
- Scalable structure for future enhancements

Future Improvements
-------------------

- Integration with persistent database systems
- Graphical User Interface (GUI) version
- Advanced seat selection visualization
- Multi-flight scheduling and management
- Enhanced validation and error handling

Author: Gerald Mathew  
“The Programmer — Flight Reservation System”

License
-------

This project is intended for educational and experimental purposes and may be updated over time.