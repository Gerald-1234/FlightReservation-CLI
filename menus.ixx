export module menus;

import std;
import users;
import flights;
import payment;

export void runCustomerSession(Customer& customer, const std::string& username);
export void runAdminSession(Admin& admin, const std::string& username);
export void runMainMenu();